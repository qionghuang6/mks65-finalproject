#include <string.h>
#include <stdlib.h>
struct Instruction {
    int cmdType;
    char ** chord;
};
struct Song{
  struct Instruction ** data;
};
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
void follow_song(){
  return 0;
}
