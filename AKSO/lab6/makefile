.PHONY: all sub square div_mul_2 div_mul_3 foo_bar_1 foo_bar_2 foo_1x foo_2x clean

all:

sub square div_mul_2 div_mul_3 foo_bar_1 foo_bar_2 foo_1x foo_2x:
	gcc -c -Wall -Wextra -std=c17 -O2 $@.c -o $@.o
	objdump -d -M intel $@.o

clean:
	rm -rf *.o
