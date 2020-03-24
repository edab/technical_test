/**
*   @file   main.c
*   @brief  Testing app for the 7bit encoder/decoder library
*
*   @author Enrico D'Abramo
*
*   @date   3/24/2020
*/
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aenc/encdec.h"

#define SLEN 128
#define TLEN 4

/**
 * @brief Print an ASCII string in HEX and Bitfield format
 *
 * @param[in]   txt_in Null-terminated ASCII string to print
 */
void print_string(char * txt) {

		printf("[");

		for (size_t i = 0; i < strlen(txt); i++) {
				printf("%02X", (unsigned char)txt[i]);
		}

		printf("]");
		printf("..[-");

		for (size_t i = 0; i < strlen(txt); i++) {
				for ( int b = 7; b >= 0; b-- ) {
						printf("%d", (txt[i] & (1 << b)) != 0);
				}
				printf("-");
		}

		printf("]\n");

}

/**
 * @brief Example application to test the library
 *
 */
int main(void)
{

	int32_t ret;

	char txt_out[SLEN];

	char test_8b[TLEN][SLEN] = { "Hello World!", \
																"Geigen", \
																"Mappets", \
																"Somewhere"};
	char test_7b[TLEN][SLEN] = { "\xC8\x32\x9B\xFD\x06\x5D\xDF\x72\x36\x39\x04", \
																"\xC7\x72\xFA\x5C\x76\x03", \
																"\xCD\x30\x1C\x5E\xA6\xCF\x01", \
																"\xD3\x77\xBB\x7C\x47\x97\xE5\x65" };

	// Encoding tests
	printf("\nTest text_7bit_encode() function\n");

	printf("\nTest uninitialized input buffer error reporting\n");
	ret = text_7bit_encode(NULL, NULL);
	assert(ret < 0);
	printf("  -> returned LIB_ERR_NULL_PTR (%d)\n", ret);

	printf("\nTest empty input buffer condition handling\n");
	ret = text_7bit_encode("", NULL);
	assert(ret == 0);
	printf("  -> returned empty string (%d)\n", ret);

	printf("\nTest single char input buffer condition handling\n");
	ret = text_7bit_encode("A", NULL);
	assert(ret == 1);
	printf("  -> returned single character string (%d)\n", ret);

	printf("\nTest non-ASCII character in input buffer condition handling\n");
	ret = text_7bit_encode("Hello Wè°orld!", txt_out);
	assert(ret == LIB_ERR_NON_ASCII);
	printf("  -> returned LIB_ERR_NULL_PTR (%d)\n", ret);

	for (int i = 0; i < TLEN; i++) {
		printf("\nTest string '%s' encoding\n", test_8b[i]);
		printf("  ->  txt_in: ");
		print_string(test_8b[i]);
		ret = text_7bit_encode(test_8b[i], txt_out);
		assert(ret == strlen(test_7b[i]));
		assert(strcmp(txt_out, test_7b[i]) == 0);
		printf("  -> txt_out: ");
		print_string(txt_out);
	}

	// Decoding tests
	printf("\nTest text_7bit_decode() function\n");

	printf("\nTest uninitialized input buffer error reporting\n");
	ret = text_7bit_decode(NULL, NULL);
	assert(ret < 0);
	printf("  -> returned LIB_ERR_NULL_PTR (%d)\n", ret);

	printf("\nTest empty input buffer condition handling\n");
	ret = text_7bit_decode("", NULL);
	assert(ret == 0);
	printf("  -> returned empty string (%d)\n", ret);

	printf("\nTest single char input buffer condition handling\n");
	ret = text_7bit_decode("A", NULL);
	assert(ret == 1);
	printf("  -> returned single character string (%d)\n", ret);

	for (int i = 0; i < TLEN; i++) {
		printf("\nTest string '%s' decoding\n", test_8b[i]);
		printf("  ->  txt_in: ");
		print_string(test_7b[i]);
		ret = text_7bit_decode(test_7b[i], txt_out);
		assert(ret == strlen(test_8b[i]));
		assert(strcmp(txt_out, test_8b[i]) == 0);
		printf("  -> txt_out: ");
		print_string(txt_out);
	}

	return EXIT_SUCCESS;

}
