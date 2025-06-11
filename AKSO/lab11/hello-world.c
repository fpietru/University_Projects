#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = getpid();

    printf("Hello from %d\n", pid);

    return 0;
}
