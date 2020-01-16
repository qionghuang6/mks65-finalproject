#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define BUFFER_SIZE 256
#define PORT "32498"
#define TEST_IP "127.0.0.1"
#define STDIN 0

void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);


#endif
