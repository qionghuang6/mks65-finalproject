#include "networking.h"
#include "parser.h"
#include <errno.h>
#include "play.h"

int main(int argc, char **argv) {

  int server_socket;
  char * buffer[2056];
  
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
    metronome();
    char s[100] = "aplay ";
    size_t i;
    int count = 10;
    for(i = 0; i < count; i++){
      strncat(s, buffer[i], 50);
      printf("%s\n", s);
      execute_note(s);
    }
    
    //execute_note()
  }
}
