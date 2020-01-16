#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>

char ** parse_args( char * line ){
  char ** args = calloc(32, sizeof(char *));
  size_t argno = 0;
  char * token = "";
  while(line != NULL && argno < 32){
    args[argno] = calloc(1,32);
    token = strsep(&line, " ");
    strncpy(args[argno], token, 32);
    argno++;
  }
  return args;
}

int execute_note(char* line){ 
    char ** args = parse_args(line);
    printf("%s\n", args[0]);
    execvp(args[0], args);
    return 0;
}

  char s[100];
int metronome(){
  strncat(s, "aplay Piano/Piano.ff.C4.wav", 30);
  printf("%s\n", s);
  while(1){
    pid_t p = fork();
    if (!p){
      execute_note(s);
    }
    sleep(1);
  }
  return 0;    
}

int main(){
    metronome();
    return 0;
}