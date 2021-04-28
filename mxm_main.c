#include "mxm_head.h"
// main file

int Cfi = 0;

int main(int argc, char *argv[]) {

  struct addrinfo hints;
  struct addrinfo *result, *rp;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
  
  if (getaddrinfo(NULL, PORTNUM, &hints, &result) != 0)
    exit(-1);
  
  int lfd, optval = 1;
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    lfd = socket(rp->ai_family, rp->ai_socktype,
		 rp->ai_protocol);
    
    if (lfd == -1)
      continue;   // On error, try next address 
    
    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR,
		   &optval, sizeof(optval)) == -1)
      exit(-1);
    
    if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
      break; // Success 

             // bind() failed, close this socket, try next address 
    close(lfd);
  }
  
  if (rp == NULL)
    exit(-1);
  
  {
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    if (getnameinfo((struct sockaddr *)rp->ai_addr, rp->ai_addrlen,
		   host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
      fprintf(stdout, "Listening on (%s, %s)\n", host, service);
    else
      exit(-1);
  }

  freeaddrinfo(result);
  
  if (listen(lfd, BACKLOG) == -1)
    exit(-1);

  pthread_attr_t tattr;
  pthread_attr_init(&tattr);
  pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);


  int n = 0;
  
  printf("please provide n > ");
  scanf("%d", &n);
  
  float defVal = 6.66;
  
  float **matrixA = initMatrix(n, defVal);
  
  float **matrixB = initMatrix(n, 3);
  
  
  for (;;)
    {
      int cfd = accept(lfd, NULL, NULL);
      if (cfd == -1) {
	continue;   // Print an error message 
      }
      
      int* argtot = (int*)malloc(sizeof(int));
      *argtot = cfd;
      
      
      pthread_t t;
      pthread_create(&t, &tattr, handleRequest, argtot);
    }
  
  pthread_attr_destroy(&tattr);
  
  exit(EXIT_SUCCESS);
}


