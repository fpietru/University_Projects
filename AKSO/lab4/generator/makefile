all: generator
generator: main.o generator.o input-output.o
	gcc -o generator main.o generator.o input-output.o

generator.o: generator.c generator.h
	gcc -c generator.c

main.o: main.c input-output.h generator.h
	gcc -c main.c

input-output.o: input-output.c input-output.h
	gcc -c input-output.c

clean:
	rm generator *.o