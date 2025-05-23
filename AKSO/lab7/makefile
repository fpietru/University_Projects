.PHONY: all foo_bar_1 foo_bar_2 mean clean

all:

foo_bar_1 foo_bar_2 mean:
	gcc -c -Wall -Wextra -std=c17 -O2 $@.c -o $@.o
	objdump -d -M intel $@.o

clean:
	rm -rf *.o
