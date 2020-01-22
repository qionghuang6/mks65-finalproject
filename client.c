#include "networking.h"
#include "parser.h"
#include <errno.h>
#include "play.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[32][200];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  void sighandler(int signo) {
  	if (signo == SIGINT){
      printf("Telling server to change state\n");
      int err = write(server_socket, "CHANGE", sizeof(buffer));
      if(err < 0){
        printf("It\'s clipped: %s\n", strerror(errno));
      }
    }
  }

  while (1) {
    signal(SIGINT, sighandler);
    int n = read(server_socket, buffer, sizeof(buffer));
    if (n < 0){
      printf("%s\n", strerror(n));
    }
    int i = 0;
    for(i = 0; strlen(buffer[i]);i++){
      char s[100] = "aplay ";
      strncat(s, buffer[i], 100);
      pid_t p = fork();
      if (!p){
        printf("<<%s>>\n",s);
        execute_note(s);
        exit(0);
      }
    }
    printf("\n");
    memset(buffer,'\0',sizeof(buffer));
    // metronome();
    // // for(i =0; i < )
    // char s[100] = "aplay ";
    // strncat(s, buffer, 100);
    // pid_t p = fork();
    // if (!p){
    //   execute_note(s);
    //   exit(0);
    // }
    sleep(1);


    //execute_note()
  }
}
