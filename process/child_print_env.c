#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char *argv[], char* env[]){
    printf("hell world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[2];
        myargs[0] = "./print_envs";
		myargs[1] = NULL;

		char *myenv[2];
		myenv[0] = "MYVAR1=10";
		myenv[1] = NULL;

		execve(myargs[0], myargs, myenv);
        printf("execv failed!\n");
    } else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
    }
    return 0;
}

