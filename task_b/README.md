# _AEnc_ 7bit ASCII encoding library

AEnc is a C library for encoding 8bit ASCII strings into a 7bit more compact form.

## Source code organization

The directory structure of this _ASCII encoder library (libaenc)_ project is:

- **doc**: contain the documentation automatically generated using Doxygen
- **src**: contain all the source code
- **src/aenc**: contain the source code of the library
- **out/api_test_app**: _testing application_ for the library
- **out/static/libaenc.a**: static _ASCII encoder library_

## Library documentation

The Library documentation can be found on the [following link](https://github.com/edab/technical_test/blob/master/task_b/doc/html/index.html).

## Compiling and Test

The library is equipped with a testing application, that will check his functionality against the rules provided.

Manual compile both the static library and the testing app:

```bash
  $ git clone git@github.com:edab/technical_test.git
  $ cd task_b
  $ make
```

Run the application:

```bash
  $ ./out/api_test_app
```
