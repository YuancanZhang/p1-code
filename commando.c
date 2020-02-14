#include "commando.h"
#include "util.c"
int main(void){

  while(1){
    printf("@> \n");
    char buffer[MAX_LINE];
    char *input = fgets(buffer,MAX_LINE,stdin);
    if(input == NULL){
      printf("End of input");
      break;
    }
    
    parse_into_tokens()
  }
}
