#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char* env[]){
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        char *myargs[2];
        myargs[0] = "ls";
        myargs[1] = NULL;

        execvp(myargs[0], myargs);
        printf("execv failed!\n");
    } else {
        sleep(1000);
        //at this point the "ls" process generated above is a zombie
        //you can check this with: ps aux | grep ls
    }
    return 0;
}

