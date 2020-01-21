#include "parser.h"
int main(int argc, char * argv[]){
  //file being sent to this program
  char * input= "test.txt";
  struct Song ** song = parseIn(input);
  printf("%s",song[0]->data[0]->chord[0]);
  return 0;
}
