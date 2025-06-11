#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error in fork (%d; %s)\n", errno, strerror(errno));
        return 1;
    }
    else if (!pid) {
        // Child process
        printf("Child: my pid is %d, my parent's pid is %d.\n", getpid(), getppid());

        // Replace the current process image to execute the "ps" command.
        execlp("ps", "ps", NULL);
        fprintf(stderr, "Error in execlp (%d; %s)\n", errno, strerror(errno));
        return 1;
    }
    else {
        // Parent process
        printf("Parent: my pid is %d, my child's pid is %d.\n", getpid(), pid);

        // Wait for child.
        pid_t child_pid = wait(NULL);
        if (child_pid == -1) {
            fprintf(stderr, "Error in the first wait (%d; %s)\n", errno, strerror(errno));
            return 1;
        }
    }

    return 0;
}
