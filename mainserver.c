#include "networking.h"
#include "parser.h"
void process(char *s);
void subserver(int from_client);

char ** parse_args( char * line ){
  char *token;
  char **out = malloc(strlen(line) * sizeof(char *));
  int i = 0;
  while(line){
    char * tmp = strsep(&line," ");
    out[i] = tmp;
    i++;
  }
  return out;
}
char * read_file(char * dir){

}

int main(int argc, char const *argv[]) {
  int instruments;
  int song_instruments;
  int connected;
  char * input;
  struct Song ** song;
  struct Instruction * cycle;
  int listen_socket;
	int rv;
  int client_sockets[64];
  int clientnum = 0;
  int time = 0;
  int paused = 0;
  int songchoice = -1;
  int songpossibilities = 4;
	int playstate = 1;

	void sighandler(int signo) {
	if (signo == SIGINT){
		printf("Interruption\n");
		if(playstate == 1){
				printf("PAUSING\n");
				playstate = 0;
				for(size_t i = 0; i < instruments; i++) {
				//write(client_sockets[i], "PAUSING", sizeof(20));
				}
			} else if(playstate == 0){
				printf("PLAYING\n");
				playstate = 1;
				for(size_t i = 0; i < instruments; i++) {
				// write(client_sockets[i], "PLAYING", sizeof(20));
				}
			}
  }
  if(signo == SIGSTOP){
    kill(getpid(), SIGKILL);
  }
}

	struct timeval tv;
  fd_set read_fds;

	//1 second timeout
	tv.tv_sec = 1;
  tv.tv_usec = 500000;

  while (songchoice < 0){
    char songentered[8];
    printf("Choose a song!\n");
    printf("1: Hot Cross Buns(Piano)\n2: It's a small world(Piano)\n3:test(Piano,Marimba)\n4:Your own music");
    fgets(songentered,7, stdin);
    printf("%d\n", atoi(songentered));
    if(atoi(songentered) < songpossibilities + 1 && atoi(songentered) > 0){
      songchoice = atoi(songentered);
    }
  }
  if(songchoice == 1){
    input = "Sheet Music/Hot Cross Buns";
  } else if (songchoice == 2){
    input = "Sheet Music/its-a-small-world.txt";
  } else if (songchoice == 3){
    input = "test.txt";
  } else{
    char tmp[256];
    printf("Your file:\n");
    fgets(tmp,256, stdin);
    tmp[strlen(tmp)-1] = '\0';
    input = tmp;
    printf("%s",input);
  }
  song = parseIn(input);
  song_instruments= getnum();
  char numInst[16];
  printf("Enter number of Instruments:");
  fgets(numInst,7, stdin);
  instruments = atoi(numInst);
  connected = 0;


  char buffers[BUFFER_SIZE][instruments];
  listen_socket = server_setup();

  while (clientnum < instruments) {
    client_sockets[clientnum] = server_connect(listen_socket);
    clientnum++;
    connected++;
    printf("Connected %d/%d\n", connected, instruments);
  }

  FD_ZERO(&read_fds);
  for (size_t i = 0; i < instruments; i++) {
    FD_SET(client_sockets[i], &read_fds);
  }
	// if (connected > 0){
	// 	for (size_t i = 0; i < instruments; i++) {
	// 		write(client_sockets[i], "Connection Established", 30);
	// 	}
	// }
  while(connected > 0){
    signal(SIGINT, sighandler);
		if(playstate == 1){
    sleep(1);
    char writestring[255] = "";
    sprintf(writestring, "time elapsed: %d", time);
		rv = select(instruments + 1, &read_fds, NULL, NULL, &tv);
		if(rv == -1) {
			perror("select");
		} else{
      int i= 0;
      while(i < instruments){
        printf("inst. number %d\n",i);
        if(FD_ISSET(client_sockets[i], &read_fds)) {
          printf("SOMEOMEHTING LSOETHING SOMETHING\n");
          read(client_sockets[i], buffers[i], sizeof(buffers[i]));
          printf("recieved: %s\n",buffers[i]);
        }
        if(song[i%song_instruments]->chlen > time){
          printf("%d|%d",song[i%song_instruments]->chlen,time);
          cycle = song[i%song_instruments]->data[time];
          printChord(cycle);
          int q = 0;
          int mx = cycle->clen;
          char send[mx][200];
          int canSend = 1;
          int size = 0;
          printf("Sending to %d:",i);
          while(q < mx){
            if((cycle->chord[q])[0] != 'r'){
              printf("| %s |", cycle->chord[q]);
              strcpy(send[q],cycle->chord[q]);
              size += strlen(send[q]);
            } else {
              canSend = 0;
              break;
            }
            q++;
          }
          memset(send[q], '\0', sizeof(send[q]));
          printf("\n");
          if(canSend){
            write(client_sockets[i], send, mx * 200 * sizeof(char));
          }else{
            printf("nevermind, no send because rest\n");
          }
        }else{

        }
        i++;
      }
      time++;
		}
  }
}
  return 0;
}
