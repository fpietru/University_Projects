all: nsqrt_example_64 testerka

nsqrt.o: nsqrt.asm
	nasm -f elf64 -w+all -w+error -o nsqrt.o nsqrt.asm

nsqrt_example_64.o: nsqrt_example.c
	gcc -c -Wall -Wextra -std=c17 -g -O2 -o nsqrt_example_64.o nsqrt_example.c

nsqrt_example_64: nsqrt_example_64.o nsqrt.o
	gcc -z noexecstack -o nsqrt_example_64 nsqrt_example_64.o nsqrt.o

testerka.o: testerka.cpp
	g++ -c -Wall -Wextra -std=c++20 -O2 -o testerka.o testerka.cpp

testerka: testerka.o nsqrt.o
	g++ -z noexecstack -o testerka testerka.o nsqrt.o -lgmp

clean:
	rm -f *.o nsqrt_example_64 testerka
