#define _GNU_SOURCE //this is needed to be able to use execvpe 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <fcntl.h>


typedef struct {
  char* binary_path;
  char* stdin;
  char* stdout;
  char* arguments;
  short wait;
} command;

//function prototypes
void print_parsed_command(command);
short parse_command(command*, char*);

// read a line from a file
short getlinedup(FILE* fp, char** value){
  char* line = NULL;
  size_t n = 0;
  //get one line
  int ret = getline(&line, &n, fp);

  if(ret == -1){
    //the file ended
    return 0;
  }
  //remove \n at the end
  line[strcspn(line, "\n")] = '\0';
  //duplicate the string and set value
  *value = strdup(line);
  free(line);

  return 1;
}

//parse a command_file and set a corresponding command data structure
short parse_command(command* parsed_command, char* cmdfile){
  FILE* fp = fopen(cmdfile, "r");
  if(!fp){
    //the file does not exist
    return 0;
  }

  char* value;
  short ret;
  int intvalue;

  ret = getlinedup(fp,&value);
  if(!ret){
    fclose(fp); return 0;
  }
  parsed_command->binary_path = value;

  ret = getlinedup(fp,&value);
  if(!ret){
    fclose(fp); return 0;
  }
  parsed_command->stdin = value;

  ret = getlinedup(fp,&value);
  if(!ret){
    fclose(fp); return 0;
  }
  parsed_command->stdout = value;

  ret = getlinedup(fp,&value);
  if(!ret){
    fclose(fp); return 0;
  }
  parsed_command->arguments = value;

  ret = getlinedup(fp,&value);
  if(!ret){
    fclose(fp); return 0;
  }
  intvalue = atoi(value);
  if(intvalue != 0 && intvalue != 1){
    fclose(fp); return 0;
  }
  parsed_command->wait = (short)intvalue;

  return 1;
}

//useful for debugging
void print_parsed_command(command parsed_command){
  printf("----------\n");
  printf("binary_path: %s\n", parsed_command.binary_path);
  printf("stdin: %s\n", parsed_command.stdin);
  printf("stdout: %s\n", parsed_command.stdout);
  printf("arguments: %s\n", parsed_command.arguments);
  printf("wait: %d\n", parsed_command.wait);
}

void free_command(command cmd){
  free(cmd.binary_path);
  free(cmd.stdin);
  free(cmd.stdout);
  free(cmd.arguments);
}


int main(int argc, char *argv[], char* env[]) {

  for(int ncommand=1; ncommand<argc; ncommand++){
    command parsed_command;
    int ret = parse_command(&parsed_command, argv[ncommand]);
    if (!ret){
      printf("command file %s is invalid\n", argv[ncommand]);
      continue;
    }

    print_parsed_command(parsed_command);

    //process_command(...);
    /*
    process_command will:
    - get a parsed_command variable
    - create a child process
    - set file redirection, arguments, envirionment variables
    - call execve or its variant
    - print when a child process is created and when any child process is terminated
    - if specified, wait for the termination of the program
    */

    free_command(parsed_command);
  }

  //remember to wait for the termination of all the child processes, regardless of the value of parsed_command.wait

}

