#include <stdio.h>

int main(int args, char *argv[], char *env[]) 
{
    int nenv = 0;
    char *cur_ev = env[nenv];
    while (cur_ev != NULL) {
        printf("%s\n", cur_ev);
        nenv++;
        cur_ev = env[nenv];
    }
    printf("There are %d env variables\n", nenv);
    return 0;
}
