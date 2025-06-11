#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error in fork (%d; %s)\n", errno, strerror(errno));
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child: my pid is %d, my parent's pid is %d.\n", getpid(), getppid());
        printf("Child: fork returned %d.\n", pid);
    }
    else {
        // Parent process
        printf("Parent: my pid is %d.\n", getpid());
        printf("Parent: fork returned %d.\n", pid);

        // Wait for child.
        pid_t child_pid = wait(NULL);
        if (child_pid == -1) {
            fprintf(stderr, "Error in the first wait (%d; %s)\n", errno, strerror(errno));
            return 1;
        }
        child_pid = wait(NULL);
        if (child_pid == -1) {
            fprintf(stderr, "Error in the second wait (%d; %s)\n", errno, strerror(errno));
            return 1;
        }
    }

    return 0;
}
