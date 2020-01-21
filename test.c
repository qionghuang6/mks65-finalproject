#include "parser.h"
int main(int argc, char * argv[]){
  //file being sent to this program
  char * input= "test.txt";
  struct Song ** song = parseIn(input);
  struct Instruction ** tick = follow(song,0);
  follow(song,1);
  follow(song,2);
  follow(song,3);
  follow(song,4);
  //debugInstuctions(tick);
  //printf("%s",song[0]->data[0]->chord[0]);
  return 0;
}
