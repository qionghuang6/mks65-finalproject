#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

char* parser_begin = "";
char* parser_end = "";
char * pb = "";
char * pe = "";
char * parse_note(char * note){
  printf("<%s%s%s>\n",pb,note,pe);
  char* out = parser_begin;
  // strcat(out,note);
  // strcat(out,parser_end);
  return out;
}
struct Instruction* parse_chord(char * chord){
  char *tmp = strtok(chord,"-");
  char ** chord_arr = (char **)malloc(sizeof(char *));
  int i = 0;
  while (tmp != NULL){
    //printf("<%s>\n",tmp);
    char *dt = tmp;
    if(tmp[0] != 'r'){
      parse_note(dt);
    }
    // char * out = malloc(sizeof(char) * strlen(dt));
    char * out = malloc(sizeof(char) * strlen(dt));
    strcpy(out,tmp);
    chord_arr[i] = out;
    i++;
    chord_arr = (char **) realloc(chord_arr, (i+1) * sizeof(char *));
    tmp = strtok(NULL,"-");
  }
  struct Instruction ch = {chord_arr};
  struct Instruction * out = (struct Instruction *) malloc(sizeof(struct Instruction));
  *out = ch;
  return out;
}
struct Song* parse_song(char * song){
  char * dup = song;
  char *tmp = strtok_r(dup," ",&dup);
  struct Song * out = (struct Song *) malloc(sizeof(struct Song));
  out->data = (struct Instruction **) malloc(sizeof(struct Instruction *));
  int i = 0;
  while(tmp != NULL){
    printf("{%s}\n",tmp);
    out->data[i] = parse_chord(tmp);
    i++;
    out->data = (struct Instruction **) realloc(out->data, (i+1) * sizeof(struct Instruction *));
    tmp = strtok_r(dup," ",&dup);
    // printf("%s",tmp);
  }
  //struct Song good = {song_data};
  //printf("dddd%sddd\n",out->data[0]->chord[0]);
  return out;
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
  int instruments = 0;
  struct Song** data = (struct Song**) malloc(sizeof(struct Song*));
  char* tmp = 0;
  FILE *fp;
  fp = fopen(dir, "r");
  while (fgets(buff, sizeof(buff), fp)) {
    // printf("%s",buff);
    if(buff[0] == '/'){
      pb = parser_begin;
      pe = parser_end;
      if((!strcmp(buff,"/piano\n")) || (!strcmp(buff,"/piano\r\n"))){
        parser_begin = "Piano/Piano.ff.";
        parser_end = ".wav";
      } else if ((!strcmp(buff,"/altosax\n")) || (!strcmp(buff,"/altosax\r\n"))){
        parser_begin = "AltoSax/AltoSax.vib.ff.";
        parser_end = ".stereo.wav";
      } else if ((!strcmp(buff,"/marimba\n")) || (!strcmp(buff,"/marimba\r\n"))){
        parser_begin = "Marimba/Marimba.yarn.ff.";
        parser_end = ".stereo.wav";
      }
      if(tmp){
         printf("[%s]\n", tmp);
        data[instruments] = parse_song(tmp);
        free(tmp);
        tmp = 0;
        instruments++;
        data = (struct Song**) realloc(data, (instruments +1) * sizeof(struct Song*));
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
  pb = parser_begin;
  pe = parser_end;
  printf("[%s]\n",tmp);
  data[instruments] = parse_song(tmp);
  free(tmp);
  printf("load success!\n");
  //printf("%s",data[0]->data[0]);
  fclose(fp);
  return data;
}
void follow_song(){
  return 0;
}
