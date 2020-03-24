/**
*   @file   encdec.c
*   @brief  Encoding and decoding source file of the libAenc library.
*
*   @author Enrico D'Abramo
*
*   @date   3/24/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "encdec.h"

#define BITMASK_7BITS 0x7F

/**
 * @brief Encode an ASCII string into a 7 bit compressed representation
 *
 * @param[in]   txt_in Null-terminated ASCII string to encode
 * @param[out]  txt_out 7-bit encoded string, null terminated
 * @return      size of the output data or error (<0)
 */
int32_t text_7bit_encode(const char* txt_in, char* txt_out) {

	if (txt_in == NULL) {
		return LIB_ERR_NULL_PTR;
	}

	// Check if the output buffer is allocated
	size_t in_len = strlen(txt_in);
	size_t out_len = ((in_len + 1) * 7 ) / 8;
	if (txt_out == NULL) {
		return out_len;
	}

	// Handle the input empty string condition
	if (in_len == 0) {
		return 0;
	}

	// Pack the data, or return an error if a non-ASCII character is detected
	// Since the behavior of the C shift operator is unknown for signed number,
	// the characters are typecasted before using them.
	size_t txt_out_idx = 0;
	uint8_t shift_bits = 0;
	size_t i = 0;
	for (; i < in_len - 1; i++) {

		if (txt_in[i] < 0) {
			return LIB_ERR_NON_ASCII;
		}

		txt_out[txt_out_idx++] = (((unsigned char)txt_in[i] & BITMASK_7BITS) >> shift_bits) |
		(((unsigned char)txt_in[i + 1] & BITMASK_7BITS) << (7 - shift_bits));

		shift_bits++;

		if (shift_bits == 7) {
			shift_bits = 0;
			++i;
		}

	}

	if (i < in_len) {
		txt_out[txt_out_idx++] = ((unsigned char)txt_in[i] & BITMASK_7BITS) >> shift_bits;
	}

	txt_out[txt_out_idx] = '\0';

	return txt_out_idx;

}

/**
 * @brief Decode a 7 bit compressed representation into a string
 *
 * @param[in]   txt_in Null-terminated 7-bit encoded string
 * @param[out]  txt_out Null-terminated decoded ASCII string
 * @return      size of the output data (>0) or error (<0)
 */
int32_t text_7bit_decode(const char* txt_in, char* txt_out) {

	if (txt_in == NULL) {
		return LIB_ERR_NULL_PTR;
	}

	// Check if the output buffer is allocated
	size_t in_len = strlen(txt_in);
	size_t out_len = in_len * 8 / 7;
	if (txt_out == NULL) {
		return out_len;
	}

	// Handle the input empty string condition
	if (in_len == 0) {
		return 0;
	}

	// UnPack the data
	// Since the behavior of the C shift operator is unknown for signed number,
	// the characters are typecasted before using them.
	size_t txt_out_idx = 0;
	uint8_t shift_bits = 1;
	size_t i = 1;

	txt_out[txt_out_idx++] = txt_in[0] & BITMASK_7BITS;

	for (; i < in_len; i++) {

		txt_out[txt_out_idx++] = BITMASK_7BITS & (((unsigned char)txt_in[i] << shift_bits) | ((unsigned char)txt_in[i - 1] >> (8 - shift_bits)));

		if (txt_out_idx == out_len) break;

		shift_bits++;

		if (shift_bits == 8) {
			shift_bits = 1;
			txt_out[txt_out_idx++] = txt_in[i] & BITMASK_7BITS;
			if (txt_out_idx == out_len) break;
		}

	}

	if (txt_out_idx < out_len) {
		if ((unsigned char)txt_in[i - 1] >> (8 - shift_bits) != 0)
			txt_out[txt_out_idx++] =	(unsigned char)txt_in[i - 1] >> (8 - shift_bits);
	}

	txt_out[txt_out_idx] = '\0';

	return txt_out_idx;
}
