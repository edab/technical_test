

## Encoding scheme

The encode function accept 8-bit ASCII characters, and compress the string by removing the most significant bit and packing such 7-bit characters in the 8-bit bytes, so that all the bits are used (each 8 character sequence would then fit in 7 bytes)

For example, consider the following string and it's hexadecimal representation:

```
ASCII string: H    e    l    l    o   
  Hex values: 0x48 0x65 0x6C 0x6C 0x6F    
```

We can represent all the chars in 8bit binary form, and also in 7bit form removing the most significant bit:

```
 8bit form: 01001000 01100101 01101100 01101100 01101111
 7bit form: .1001000 .1100101 .1101100 .1101100 .1101111
```

Now we move the LSB bit from the 2nd byte to the MSB bit of the 1st byte:

```
                            *
  Move bit: .1001000 .110010. .1101100 .1101100 .1101111
  Move bit: 11001000 .110010. .1101100 .1101100 .1101111
            *
```

We can shift the 2nd byte by one space, the one free:

```
                      ------>
     Shift: 11001000 .110010. .1101100 .1101100 .1101111
     Shift: 11001000 ..110010 .1101100 .1101100 .1101111
```

And we can repeat the first step, taking this time 2 LSB bits from the 3rd character:

```
                                    **
 Move bits: 11001000 ..110010 .11011.. .1101100 .1101111
 Move bits: 11001000 00110010 .1101100 .1101100 .1101111
                     **
```

And repeat this process for every character, obtaining:

```
    Result: 11001000 00110010 10011011 11111101 00000110
Hex values: 0xC8     0x32     0x9B     0xFD     0x06
```
