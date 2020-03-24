all: app

out/main.o: src/main.c
	gcc -std=c99 -Wall -c src/main.c -o out/main.o

out/static/encdec.o: src/aenc/encdec.c
	gcc -std=c99 -Wall -c src/aenc/encdec.c -o out/static/encdec.o

lib: out/static/encdec.o
	ar rcs out/static/libaenc.a out/static/encdec.o

app: lib out/main.o
	gcc -Wall -std=c99 out/main.o -Lout/static -laenc -o out/api_test_app

clean:
	rm -f out/main.o
	rm -f out/static/encdec.o
	rm -f out/static/libaenc.a
	rm -f out/api_test_app
