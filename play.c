#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>

char ** parse_args( char * line ){
  char ** args = calloc(50, sizeof(char *));
  size_t argno = 0;
  char * token = "";
  while(line != NULL && argno < 50){
    args[argno] = calloc(1,50);
    token = strsep(&line, " ");
    strncpy(args[argno], token, 50);
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

  char s[150];
int metronome(){
  strncat(s, "aplay AltoSax/AltoSax.vib.ff.C4.stereo.wav", 50);
  printf("%s\n", s);
  while(1){
    pid_t p = fork();
    if (!p){
      execute_note(s);
    }
    sleep(2);
  }
  return 0;    
}

int main(){
    metronome();
    return 0;
}