CC = gcc
CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2
LDFLAGS = -shared -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc \
          -Wl,--wrap=reallocarray -Wl,--wrap=free -Wl,--wrap=strdup -Wl,--wrap=strndup

SRC = ma.c memory_tests.c
OBJ = ma.o memory_tests.o
LIB = libma.so

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

ma.o: ma.c ma.h
	$(CC) $(CFLAGS) -c ma.c -o ma.o

memory_tests.o: memory_tests.c memory_tests.h
	$(CC) $(CFLAGS) -c memory_tests.c -o memory_tests.o

clean:
	rm -f $(OBJ) $(LIB)

