# Ścieżki do plików w katalogu głównym
SOLUTION = ../ma.c
HEADERS  = ../
LIBDIR   = ..
LIB      = $(LIBDIR)/libma.so

CC       = gcc
CPPFLAGS =
CFLAGS   = -g -Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2 -I$(HEADERS)
LDFLAGS  =

vpath %.h $(HEADERS)

.PHONY: all clean test

all: $(LIB) ma_tests

# Budowanie biblioteki libma.so z katalogu głównego
$(LIB):
	$(MAKE) -C $(LIBDIR) libma.so

ma_tests.o: ma_tests.c ma.h memory_tests.h

ma_tests: ma_tests.o $(LIB)
	$(CC) -g -L$(LIBDIR) -o $@ $< -lma -Wl,-rpath=$(LIBDIR)

test: ma_tests
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LIBDIR); \
	for test in one two connections undetermined delete params malicious pipeline shift cycle alloc memory weak disconnect; do \
		if /bin/time -f%U ./ma_tests "$$test" && \
		   valgrind -q --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./ma_tests "$$test"; then \
			echo "$$test pass"; \
		else \
			echo "$$test fail"; \
		fi; \
	done

clean:
	rm -f ma_tests.o ma_tests
	$(MAKE) -C $(LIBDIR) clean