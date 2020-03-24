/**
*   @file   encdec.c
*   @brief  Encoding and decoding header file of the libAenc library.
*
*   @author Enrico D'Abramo
*
*   @date   3/24/2020
*/
#include <stdint.h>

#define LIB_ERR_NULL_PTR    -1
#define LIB_ERR_NON_ASCII   -2

/**
 * @brief Encode an ASCII string into a 7 bit compressed representation
 *
 * @param[in]   txt_in Null-terminated ASCII string to encode
 * @param[out]  txt_out 7-bit encoded string, null terminated
 * @return      size of the output data or error_code (<0)
 */
int32_t text_7bit_encode(const char* txt_in, char* txt_out);

/**
 * @brief Decode a 7 bit compressed representation into a string
 *
 * @param[in]   txt_in Null-terminated 7-bit encoded string
 * @param[out]  txt_out Null-terminated decoded ASCII string
 * @return      size of the output data (>0) or error_code (<0)
 */
int32_t text_7bit_decode(const char* txt_in, char* txt_out);
