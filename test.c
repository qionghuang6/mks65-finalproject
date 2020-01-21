#include "parser.h"
int main(int argc, char * argv[]){
  //file being sent to this program
  char * input= "test.txt";
  struct Song ** song = parseIn(input);
  int i = 0;
  struct Instruction ** tick = follow(song,0);
  printf("jjj%pjjj\n",tick);
  while (tick = follow(song,i)){
    int b = 0;

    for(;b< 1;b++){
      // && tick[b]->chord[0] != 'r'
      // if(tick[b] != 0){
      //   printf("sdfsdf");
      //   //printf("%s",tick[b]->chord[0]);
      // }
    }
    printf("------\n");
    i++;
  }

  //debugInstuctions(tick);
  //printf("%s",song[0]->data[0]->chord[0]);
  return 0;
}
