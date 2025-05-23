.PHONY: all test clean

vpath %.asm ../rozwiazania

all: max_test delay_jz_jn_test delay_jrcxz_loop_test mean_test

max.o: max.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

max_test.o: max_test.c
	gcc -c -Wall -Wextra -Wno-sign-compare -std=c17 -O2 -o $@ $<

max_test: max.o max_test.o
	gcc -z noexecstack -o $@ $^

delay_jz_jnz.o: delay_jz_jnz.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

delay_jrcxz_loop.o: delay_jrcxz_loop.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

delay_test.o: delay_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

delay_jz_jn_test: delay_jz_jnz.o delay_test.o
	gcc -z noexecstack -o $@ $^

delay_jrcxz_loop_test: delay_jrcxz_loop.o delay_test.o
	gcc -z noexecstack -o $@ $^

mean.o: mean.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

mean_test.o: mean_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

mean_test: mean.o mean_test.o
	gcc -z noexecstack -o $@ $^

test:
	./max_test; ./mean_test

clean:
	rm -rf *_test *.o
