#define _BSD_SOURCE /* For NI_MAXHOST and NI_MAXSERV */
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>

#define PORTNUM "49999"    /* Port number for server */
#define BACKLOG 128
#define BUFSIZE 64

int Cfi;

#include <math.h>


float **initMatrix(int n, float value);

void printSquareMatrix(int n, float** matrix);

void *handleRequest(void* input);
