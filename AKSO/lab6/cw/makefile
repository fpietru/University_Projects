.PHONY: all test clean

vpath %.asm ../rozwiazania

all: mac0_test mac1_test mac2_test

mac0.o: mac0.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

mac0_test.o: mac0_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

mac0_test: mac0.o mac0_test.o
	gcc -z noexecstack -o $@ $^

mac1.o: mac1.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

mac1_test.o: mac1_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

mac1_test: mac1.o mac1_test.o
	gcc -z noexecstack -o $@ $^

mac2.o: mac2.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

mac2_test.o: mac2_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

mac2_test: mac2.o mac2_test.o
	gcc -z noexecstack -o $@ $^

test:
	./mac0_test; ./mac1_test; ./mac2_test

clean:
	rm -rf mac?_test *.o
