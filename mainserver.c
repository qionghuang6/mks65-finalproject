#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main(int argc, char const *argv[]) {
  int instruments;
  int listen_socket;
  int f;
  int client_sockets[64];
  int clientnum;
  if(argc == 0){
    printf("tell me how many instruments u wanna use!\n" );
    return 1;
  }else{
    instruments = argv[0];
  }
  listen_socket = server_setup();

  while (clientnum < instruments) {
    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0){
      subserver(client_socket);
    }else{

    }
  }

  return 0;
}

// void subserver(int client_socket) {
//   char buffer[BUFFER_SIZE];
//
//   while (read(client_socket, buffer, sizeof(buffer))) {
//
//     printf("[subserver %d] received: [%s]\n", getpid(), buffer);
//     char writestring[255];
//     sprintf(writestring, "%s %d: ", "recived by", getpid());
//     strncat(writestring, buffer, 128);
//     write(client_socket, writestring, sizeof(writestring));
//   }//end read loop
//   close(client_socket);
//   exit(0);
// }
