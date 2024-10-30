CFLAGS = -std=c17 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond\
	-Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init\
	-Wlogical-not-parentheses -Wnull-dereference -Wvla -Werror\
	-fstack-protector-strong -fsanitize=undefined -fno-sanitize-recover\
	-g -fno-omit-frame-pointer -O1

ocen.e: ocen.c zbior_ary.c zbior_ary.h
	gcc $(CFLAGS) ocen.c zbior_ary.c -o ocen.e

clean:
	rm -f *.e