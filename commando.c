#include "commando.h"

int main(int argc, char* argv[]){
  setvbuf(stdout,NULL,_IONBF, 0);
  setenv("COMMANDO_ECHO","hehe",1);
  cmdcol_t* newcol = malloc(sizeof(cmdcol_t));
  while(1){
    printf("@> ");
    char buffer[MAX_LINE];
    char *input = fgets(buffer,MAX_LINE,stdin);
    if(!input){
      printf("End of input\n");
      break;
    }
    int argcc = 0;
    char* argvv[ARG_MAX+1];
    parse_into_tokens(buffer,argvv,&argcc);
    if(argcc == 0){                     //if no input (use of enter)
      break;
    }

    if(getenv("COMMANDO_ECHO")||strcmp(argv[1],"--echo") == 0){
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
    if(strcmp(argvv[0],"help") == 0){
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
    else if(strcmp(argvv[0],"exit") == 0){
      exit(0);
    }
    else if(strcmp(argvv[0],"list") == 0){
      cmdcol_print(newcol);
    }
    else if(strcmp(argvv[0],"pause") == 0){
      long nanos = atol(argvv[1]);
      int secs = atoi(argvv[2]);
      pause_for(nanos,secs);
      cmdcol_update_state(newcol,NOBLOCK);
    }
    else if(strcmp(argvv[0],"output-for") == 0){
      int jobn = atoi(argvv[1]);
      printf("@<<< Output for %s[#%d] (%d bytes)\n",newcol->cmd[jobn]->name,newcol->cmd[jobn]->pid,newcol->cmd[jobn]->output_size);
      cmd_print_output(newcol->cmd[jobn]);
    }
    else if(strcmp(argvv[0],"output-all") == 0){
      for(int i = 0; i<newcol->size; i++){
        printf("@<<< Output for %s[#%d] (%d bytes)\n",newcol->cmd[i]->name,newcol->cmd[i]->pid,newcol->cmd[i]->output_size);
        cmd_print_output(newcol->cmd[i]);
      }
    }
    else if(strcmp(argvv[0],"wait-for") == 0){
      int jobn = atoi(argvv[1]);
      cmd_update_state(newcol->cmd[jobn],DOBLOCK);
    }
    else if(strcmp(argvv[0],"wait-all") == 0){
      for(int i = 0; i<newcol->size; i++){
        cmd_update_state(newcol->cmd[i],DOBLOCK);
      }
    }
    else{
      cmd_t* newcmd = cmd_new(argvv);
      cmdcol_add(newcol,newcmd);
      cmd_start(newcmd);
    }

    cmdcol_update_state(newcol,NOBLOCK);

  }

  cmdcol_freeall(newcol);
  return 0;
}
