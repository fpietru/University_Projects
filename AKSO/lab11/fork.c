#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    printf("Hello from %d\n", getpid());

    // Fork into two processes.
    if (fork() == -1) {
        fprintf(stderr, "Error in fork (%d; %s)\n", errno, strerror(errno));
        return 1;
    }

    printf("Goodbye from %d\n", getpid());

    return 0;
}
