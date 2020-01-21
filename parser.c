#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

char * parse_note(char * note, char * start, char * end){
  char* out = start;
  strcat(out,note);
  strcat(out,end);
  return out;
}
struct Instruction* parse_chord(char * chord){
  char *tmp = strtok(chord,"-");
  char ** chord_arr = (char **)malloc(sizeof(char *));
  int i = 0;
  while (tmp != NULL){
    // printf("<%s>\n",tmp);
    chord_arr[i] = tmp;
    i++;
    chord_arr = (char **) realloc(chord_arr, (i+1) * sizeof(char *));
    tmp = strtok(NULL,"-");
  }
  struct Instruction ch = {chord_arr};
  struct Instruction * out = malloc(sizeof(struct Instruction));
  *out = ch;
  return out;
}
struct Song* parse_song(char * song){
  char * dup = song;
  char *tmp = strtok_r(dup," ",&dup);
  struct Instruction ** song_data = malloc(sizeof(struct Instruction *));
  int i = 0;
  while(tmp != NULL){
    // printf("{%s}\n",tmp);
    song_data[i] = parse_chord(tmp);
    i++;
    song_data = (struct Instruction **) realloc(song_data, (i+1) * sizeof(struct Instruction *));
    tmp = strtok_r(dup," ",&dup);
    // printf("%s",tmp);
  }
  return song_data;
}
char* concat(char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    free(s1);
    strcat(result, " ");
    // printf("%s",result);
    strncat(result, s2, strlen(s2) - 1);
    return result;
}
struct Song ** parseIn(char* dir){
  char buff[1024];
  int instruments = 1;
  struct Song** data = malloc(sizeof(struct Song*));
  char* tmp = 0;
  FILE *fp;
  fp = fopen(dir, "r");
  while (fgets(buff, sizeof(buff), fp)) {
    // printf("%s",buff);
    if(buff[0] == '\\'){
      if(tmp){
        // printf("[%s]\n", tmp);
        data[instruments] = parse_song(tmp);
        free(tmp);
        tmp = 0;
        instruments++;
        data = realloc(data, instruments * sizeof(struct Song*));
      }
    }else{
      if(tmp){
        tmp = concat(tmp,buff);
      }else{
        tmp = calloc((strlen(buff)), sizeof(char *) );
        tmp[strlen(buff)] = "\0";
        strncpy(tmp, buff, strlen(buff)-1);
      }
    }
  }
  data[instruments] = parse_song(tmp);
  free(tmp);
  printf("load success!\n");
  fclose(fp);
  return data;
}
void follow_song(){
  return 0;
}
