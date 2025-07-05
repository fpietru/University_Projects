CC = gcc
CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2
LDFLAGS = -shared -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=reallocarray -Wl,--wrap=free -Wl,--wrap=strdup -Wl,--wrap=strndup
SOURCES = ma.c memory_tests.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = libma.so

.PHONY: all clean test example

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

example: all ma_example.c
	$(CC) $(CFLAGS) ma_example.c -lma -L. -Wl,-rpath=. -o example

clean:
	rm -f *.o *.so example
