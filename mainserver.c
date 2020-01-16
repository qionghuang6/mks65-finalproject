#include "networking.h"

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
	if (signo == SIGINT){
		printf("trying to pause or play");
  }else{
		printf("YEET\n" );
	}
}

int main(int argc, char const *argv[]) {
  int instruments;
  int connected;
  int listen_socket;
  int f;
  int client_sockets[64];
  int clientnum = 0;
  char buffer[BUFFER_SIZE];
  int time = 0;
  int paused = 0;
  int songchoice = -1;
  int songpossibilities = 2;
	struct timeval tv;
  fd_set read_fds;

	//1 second timeout
	tv.tv_sec = 1;
  tv.tv_usec = 500000;

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
    printf("Connected %d/%d\n", connected, instruments);
  }

	FD_ZERO(&read_fds);
	FD_SET(STDIN_FILENO, &read_fds);
	for (size_t i = 0; i < instruments; i++) {
		FD_SET(client_sockets[i], &read_fds);
	}

  while (songchoice < 0){
    char songentered[8];
    printf("Choose a song!\n");
    printf("1: Hot Cross Buns\n2: Fortunate Son\n");
    fgets(songentered,7, stdin);
    printf("%d\n", atoi(songentered));
    if(atoi(songentered) < songpossibilities + 1 && atoi(songentered) > 0){
      songchoice = atoi(songentered);
    }
  }

  while(connected > 0){
    signal(SIGINT, sighandler);
    time++;
    sleep(0.1);
    char writestring[255] = "";
    sprintf(writestring, "time elapsed: %d", time);
		select(instruments + 1, &read_fds, NULL, NULL, &tv);

    if (FD_ISSET(STDIN, &read_fds)) {
        printf("A key was pressed!\n");

		}

    for(size_t i = 0; i < instruments; i++) {
			if(FD_ISSET(client_sockets[i], &read_fds)) {
        read(client_sockets[i], buffer, sizeof(buffer));
				printf("recieved: %s\n",buffer);
			}
      //write(client_sockets[i], writestring, sizeof(writestring));
    }
  }
  return 0;
}
