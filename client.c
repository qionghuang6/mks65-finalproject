#include "networking.h"
#include "parser.h"
#include <errno.h>
#include "play.h"

int main(int argc, char **argv) {

  int server_socket;
  struct Instruction buffer[BUFFER_SIZE];

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
    read(server_socket, buffer, sizeof(buffer));
    metronome();
    char** notes = buffer->chord;
    while (buffer->chord){
    execute_note(notes);
    notes++;
    }
  }
}
