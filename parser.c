#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
//Made by Kevin Cai
char* parser_begin = "";
char* parser_end = "";
char * pb = "";
char * pe = "";
int NUM_INSTRUMENTS = 0;
struct Instruction* parse_chord(char * chord){
  char *tmp = strtok(chord,"-");
  char ** chord_arr = (char **)malloc(sizeof(char *));
  int i = 0;
  while (tmp != NULL){
    printf("<%s>\n",tmp);
    char *dt;
    if(tmp[0] != 'r'){
      dt = malloc(sizeof(char) * (strlen(tmp)+strlen(pb)+strlen(pe) +1));
      strcpy(dt,pb);
      strcat(dt,tmp);
      strcat(dt,pe);
    }else{
      dt = malloc(sizeof(tmp));
      strcpy(dt,tmp);
    }
    chord_arr[i] = dt;
    printf("<%s>\n",dt);
    i++;
    chord_arr = (char **) realloc(chord_arr, (i+1) * sizeof(char *));
    tmp = strtok(NULL,"-");
  }
  struct Instruction ch = {chord_arr,i};
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
    //printf("%s",tmp);
  }
  //printf("%d",i);
  out->chlen = i;
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
      NUM_INSTRUMENTS++;
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
struct Instruction** follow(struct Song ** song,int tick){
  int inst = 0;
  int isGood = 0;
  //printf("||||||%s\n",song[0]->data[3]->chord[0]);
  // printf("%d\n",song[inst]->data[tick];);
  struct Instruction** cycle = (struct Instruction**) malloc(sizeof(struct Instruction*));
  while(inst < NUM_INSTRUMENTS){
    if(song[inst]->chlen > tick){
      printf("%d|%d",song[inst]->chlen,tick);

      isGood = 1;
      cycle[inst] = song[inst]->data[tick];
      printChord(cycle[inst]);
    }else{

    }
    inst++;
    cycle = (struct Instruction**) realloc(cycle, (inst+1)* sizeof(struct Instruction*));
  }
  //cycle = (struct Instruction**) realloc(cycle, (inst)* sizeof(struct Instruction*));
  //printf("----------\n");
  if(isGood){
    printf("kkkk%pkkkkk\n",cycle);
    return cycle;
  }else{
    return 0;
  }
}
void printChord(struct Instruction* inst){
  int i = 0;
  int mx = inst->clen;
  while(i < mx){
    printf("|%s|", inst->chord[i]);
    i++;
  }
  printf("\n");
}
