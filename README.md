# Task A

> Suggest a proper LDO for supplying [Acconeer A111](https://github.com/edab/technical_test/blob/master/task_a/Acconeer%20A111%20datasheet.pdf) Radar Sensor and give a reason why it is the best solution and the others might not be. The sensor is used in a battery powered device, so it is very important to use as little power as possible.
>
> You can choose between:
>
> - [AP2112K-1.8TRG1](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP2112K-1.8TRG1.pdf)
> - [TPS78233DDCT](https://github.com/edab/technical_test/blob/master/task_a/TI%20TPS78233DDCT.pdf)
> - [AP7354-18SF4-R7](https://github.com/edab/technical_test/blob/master/task_a/Diodes%20AP7354-18SF4-R7.pdf)

# Task B

Write a library with the API specified below, and the application to test it. The project should contain at least 2 source .c files, and a Makefile necessary to build it. The sources shall be buildable on any POSIX system.

The API:

```C
int32_t text_7bit_encode(const char* txt_in, char* txt_out);
```

- **txt_in**: null-terminated ASCII string to encode,
- **txt_out**: 7-bit encoded string, null terminated (the implementation has to make sure there is a \0 value at the end), the function should return the size of the output data (>0) or error (<0).

```C
int32_t text_7bit_decode(const char* txt_in, char* txt_out);
```

- **txt_in**: null-terminated 7-bit encoded string,
- **txt_out**: null-terminated decoded ASCII string, the function should return the size of the output data (>0) or error (<0).


The functions should check the correctness of their parameters (NULL pointers, non-ASCII characters) and report the errors, but accept and ignore the NULL as the second parameter.

The `encode` function should take the 8-bit ASCII characters, and compress the string by removing the most significant bit and packing such 7-bit characters in the 8-bit bytes, so that all the bits are used (each 8 character sequence would then fit in 7 bytes)

> for example:
> for 2 characters in the original string, the 7 bits of the first byte of the encoded string would contain the 7 bits of the original ASCII character, the most significant bit of this first byte would be the least significant bit of the second ASCII character, and the second byte of the encoded string would contain the remaining 6 bits of the second ASCII character.

The `decode` function would take such a compressed string and "unpack" it, putting all the 7-bit characters back in their own bytes, with their most significant bit 0.

The testing application should demonstrate the correctness of the implementation.

The functions and their API should be documented.
