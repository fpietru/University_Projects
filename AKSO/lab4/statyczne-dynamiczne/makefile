CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -O2 -std=c17

.PHONY: all clean

all: example_dynamic example_static

decrement.o: decrement.c byone.h
increment.o: increment.c byone.h
example.o: example.c byone.h

libbyone.a: increment.o decrement.o
	ar -rcs $@ $^

libbyone.so: increment.o decrement.o
	gcc -shared -o $@ $^

example_static: example.o libbyone.a
	gcc -static -L. -o $@ $< -lbyone

example_dynamic: example.o libbyone.so
	gcc -L. -o $@ $< -lbyone

clean:
	rm -rf example_dynamic example_static *.a *.so *.o
