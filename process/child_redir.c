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
        char *myargs[3];
        myargs[0] = "ls";
        myargs[1] = "-la";
        myargs[2] = NULL;

        int fd = open("stdout_file", O_WRONLY|O_CREAT|O_TRUNC, 0664); /*open the file */
        dup2(fd,STDOUT_FILENO); /*copy the file descriptor fd into standard output*/
        close(fd);

		execvp(myargs[0], myargs);
        printf("execv failed!\n");
    } else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
    }
    return 0;
}

