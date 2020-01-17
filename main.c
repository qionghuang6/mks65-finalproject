#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <parser.c>
char ** parse_args( char * line ){
  char *token;
  char **out = malloc(strlen(line) * sizeof(char *));
  int i = 0;
  while(line){
    char * tmp = strsep(&line," ");
    out[i] = tmp;
    i++;
  }
  return out;
}
char * read_file(char * dir){

}
int main(int argc, char * argv[]){
  char input[256] = "";
  int j = 1;
  if (argc > 1) {
      while(j < argc){
        if(strlen(argv[j]) > 1){
          strcat(input, argv[j]);
          strcat(input, " ");
        }
        j++;
      }
  } else {
      printf("Please enter a file to play:");
      fgets(input, 254, stdin);
  }
  input[strlen(input)-1] = '\0';
  char ** test = parse_args(input);
  struct Song** main_song = 0;

  return 0;
}
