#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

const struct Instruments{
  char *inst[3];
} Instruments = {"Piano" , "Marimba", "AltoSax"};
const int NUM_INSTRUMENTS = sizeof(Instruments.inst);

char * parse_note(char * note, char * start, char * end){
  char* out = start;
  strcat(out,note);
  strcat(out,end);
  return out;
}
char ** parse_chord(char * chord){
  char * counter = chord;
  char ** chord_arr = (char **)calloc(1,sizeof(char *));
  int i = 0;
  while (*counter){
    counter = strtok(counter,"-");
    chord_arr[i] = counter;
    chord_arr = (char **) realloc(i+1, sizeof(char *));
    counter++;
    i++;
  }
  return chord_arr;
}
struct Song* parse_song(char * song){
  char ** chord_arr = (char **)calloc(1, sizeof(char *));
  int i = 0;
  while(*song){
    song = strtok(song," ");
    chord_arr[i] = parse_chord(song);
    chord_arr = (char **) realloc(i+1, sizeof(char *));
    i++;
    song++;
  }
  //TODO: finish this func
  return 0;
}
struct Song ** parse_file(char * song){
  struct Song ** output = (struct Song **)calloc(1, sizeof(struct Song *));
  int i  = 0;
  while(*song){
    song = strtok(song, "/");
    output[i] = parse_song(song);
    output = (struct Song **)realloc(i+1, sizeof(struct Song *));
    song++;
    i++;
  }
  return output;
}
char* concat(char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    free(s1);
    strcat(result, " ");
    strncat(result, s2, strlen(s2) - 1);
    return result;
}
struct Song ** parseIn(char* dir){
  char buff[1024];
  int instruments = 0;
  struct Song** data = malloc(sizeof(struct Song*) * NUM_INSTRUMENTS);
  char* tmp = 0;
  FILE *fp;
  fp = fopen(dir, "r");
  while (fgets(buff, sizeof(buff), fp)) {
    printf("%s",buff);
    if(buff[0] == '\\'){
      if(tmp){
        printf("[%s]\n", tmp);
        //TODO: parse song
        //data[instruments] = parse_song(tmp);
        free(tmp);
        tmp = 0;
        instruments++;
      }
    }else{
      if(tmp){
        tmp = concat(tmp,buff);
      }else{
        tmp = malloc(sizeof(char *) * strlen(buff));
        strncpy(tmp, buff, strlen(buff) - 1);
      }
    }
  }
  printf("[%s]\n", tmp);
  //data[instruments] = parse_song(tmp);
  free(tmp);
  printf("load success!\n");
  fclose(fp);
  return data;
}
void follow_song(){
  return 0;
}
