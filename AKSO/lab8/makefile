.PHONY: all clean

vpath %.asm ../rozwiazania

all: counter_test hello_test transform_test caller_test

counter.o: counter.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

counter_test.o: counter_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

counter_test: counter.o counter_test.o
	gcc -z noexecstack -o $@ $^

hello.o: hello.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

hello_test.o: hello_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

hello_test: hello.o hello_test.o
	gcc -z noexecstack -o $@ $^

called.o: called.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

transform.o: transform.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

transform_test.o: transform_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

transform_test: transform.o transform_test.o
	gcc -z noexecstack -o $@ $^

caller.o: caller.asm
	nasm -f elf64 -w+all -w+error -o $@ $<

caller_test.o: caller_test.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o $@ $<

caller_test: caller.o called.o caller_test.o
	gcc -z noexecstack -o $@ $^

clean:
	rm -rf *_test *.o
