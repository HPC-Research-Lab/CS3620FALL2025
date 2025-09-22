#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3

int main() {
    pid_t pids[NUM_CHILDREN];

    // Fork multiple children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            // Child process
            printf("Child %d (PID=%d) started\n", i, getpid());
            sleep(1 + i);  // Simulate work
            printf("Child %d (PID=%d) exiting\n", i, getpid());
            exit(10 + i);  // Exit with unique code
        }
        // Parent stores child PID
        pids[i] = pid;
    }

    // Parent waits for all children
    for (int remaining = NUM_CHILDREN; remaining > 0; ) {
        int status;
        pid_t pid = waitpid(-1, &status, 0);  // -1 waits for any child
        if (pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Parent: Child PID=%d exited with code %d\n",
                   pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent: Child PID=%d killed by signal %d\n",
                   pid, WTERMSIG(status));
        }
        remaining--;
    }

    printf("Parent: All children have exited.\n");
    return 0;
}

