#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main(int argc, char const *argv[]) {
  int instruments;
  int connected;
  int listen_socket;
  int f;
  int client_sockets[64];
  int clientnum = 0;
  char buffer[BUFFER_SIZE];

  if(argc <= 1){
    printf("tell me how many instruments u wanna use!\n" );
    return 1;
  }else{
    instruments = atoi(argv[1]);
    connected = 0;
  }
  listen_socket = server_setup();

  while (clientnum < instruments) {
    client_sockets[clientnum] = server_connect(listen_socket);
    clientnum++;
    connected++;
  }
  printf("CONNECTED %d\n", connected);
  while(connected > 0){
    for(size_t i = 0; i < instruments; i++) {
      if (read(client_sockets[i], buffer, sizeof(buffer))) {
          char writestring[255] = "";
          sprintf(writestring, "Socket %ld recieved: ", i);
          strncat(writestring, buffer, 128);
          printf("%s\n", writestring);
          write(client_sockets[i], writestring, sizeof(writestring));
        } else{
          printf("DISCONNECTED\n");
          connected--;
      }
    }
  }

  return 0;
}
