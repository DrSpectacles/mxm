#include "mxm_head.h"

float **initMatrix(int n, float value) {

  printf("initMatrix call, n = %d, val = %.2f \n", n, value);

  float **matrix;

  matrix = (float**) malloc(sizeof (float *) * n);

  for (int a = 0; a < n; a++) {
      matrix[a] = (float*) malloc(sizeof (float) * n);
  }

  for (int x = 0; x < n; x++) {

    for (int y = 0; y < n; y++) {
      matrix[x][y] = value;
    }
  }

  return matrix; 
}

void printSquareMatrix(int n, float** matrix) {

  puts("");
    
  for (int y = 0; y < n; y++) {

    printf("| ");

    for (int x = 0; x < n; x++) {

      printf(" %.2f ", matrix[x][y]);

    }
    
    printf(" | \n"); 
  }
}


void *handleRequest(void* input)
{
  Cfi++;
  int cfd = *(int*)input;

  char buf[BUFSIZE];
  ssize_t numRead;
  while ((numRead = read(cfd, buf, BUFSIZE)) > 0) {
    printf("got string |%s|, connection no. %d \n", buf, Cfi);
    if (write(cfd, buf, numRead) != numRead) {
      fprintf(stderr, "Write error. errno %d.\n", errno);
    }
  }

  if (numRead == -1) {
    fprintf(stderr, "Read error. errno %d.\n", errno);
  }
  
  
  if (close(cfd) == -1) /* Close connection */
    {
      fprintf(stderr, "close error. errno %d.\n", errno);
    }
  
  free(input);
  
  pthread_exit(NULL);
  return NULL;
}
