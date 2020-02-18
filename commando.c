#include "commando.h"
#include "util.c"

int main(int argc, char* argv[]){
  setvbuf(stdout,NULL,_IONBF, 0)
  setenv("COMMANDO_ECHO","hehe",1);
  while(1){
    printf("@> ");
    char buffer[MAX_LINE];
    char *input = fgets(buffer,MAX_LINE,stdin);
    if(input == NULL){
      printf("End of input\n");
      break;
    }
    int* argcc;
    char* argvv;
    parse_into_tokens(buffer,argvv,argcc);
    if(argcc == 0){                     //if no input (use of enter)
      break;
    }

    if(getenv("COMMANDO_ECHO")){
      printf("%s\n",argvv[0]);
    }
    // @> help
    // COMMANDO COMMANDS
    // help               : show this message
    // exit               : exit the program
    // list               : list all jobs that have been started giving information on each
    // pause nanos secs   : pause for the given number of nanseconds and seconds
    // output-for int     : print the output for given job number
    // output-all         : print output for all jobs
    // wait-for int       : wait until the given job number finishes
    // wait-all           : wait for all jobs to finish
    // command arg1 ...   : non-built-in is run as a job
    if(strcmp(argvv[0],"help")){
      printf("COMMANDO COMMANDS\n");
      printf("help               : show this message\n");
      printf("exit               : exit the program\n");
      printf("list               : list all jobs that have been started giving information on each\n");
      printf("pause nanos secs   : pause for the given number of nanseconds and seconds\n");
      printf("output-for int     : print the output for given job number\n");
      printf("output-all         : print output for all jobs\n");
      printf("wait-for int       : wait until the given job number finishes\n");
      printf("wait-all           : wait for all jobs to finish\n");
      printf("command arg1 ...   : non-built-in is run as a job\n");
    }
    else if(strcmp(argvv[0],"exit")){
      exit(0);
    }
    else if(strcmp(argvv[0],"list")){}
    else if(strcmp(argvv[0],"pause")){}
    else if(strcmp(argvv[0],"output-for")){}
    else if(strcmp(argvv[0],"output-all")){}
    else if(strcmp(argvv[0],"wait-for")){}
    else if(strcmp(argvv[0],"wait-all")){}
    else if(strcmp(argvv[0],"command")){}
    else{

    }

  }
  return 0;
}
