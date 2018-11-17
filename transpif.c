#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void printmat (int* matrix, int width);

int main (int argc, char**argv) {
  if (argc != 3) {
    fprintf(stderr,
	    "Wrong number of command-line arguments\nUsage: %s <Matrix width> <Block width>\n", argv[0]);
    return -1;
  }

  int matwidth = atoi(argv[1]);
  int blockwidth = atoi(argv[2]);
  if (blockwidth < 1) {
    printf("Invalid block width being replaced with 1\n");
    blockwidth = 1;
  }

  int* matrix = malloc(matwidth*matwidth*sizeof(int));

  for (int i = 0; i < matwidth*matwidth; i++) {
    matrix[i] = rand();
    //matrix[i] = i;
  }

  struct timeval starttime;
  gettimeofday(&starttime, NULL);
  
  int tmp;
  //printmat(matrix, matwidth);
  for (int i = 0; i < matwidth; i += blockwidth) {
    for (int j = i; j < matwidth; j += blockwidth) {
      if (j == i) {
	for (int k = 0; k < blockwidth; k++) {
	  for (int l = k+1; l < blockwidth; l++) {
	    tmp = matrix[(i+k)*matwidth + j + l];
	    matrix[(i+k)*matwidth + j + l] = matrix[(j+l)*matwidth + i + k];
	    matrix[(j+l)*matwidth + i + k] = tmp;
	  }
	}
      } else {
	for (int k = 0; k < blockwidth; k++) {
	  for (int l = 0; l < blockwidth; l++) {
	    tmp = matrix[(i+k)*matwidth + j + l];
	    matrix[(i+k)*matwidth + j + l] = matrix[(j+l)*matwidth + i + k];
	    matrix[(j+l)*matwidth + i + k] = tmp;
	  }
	}
      }
    }
  }
  struct timeval endtime;
  gettimeofday(&endtime, NULL);
  printf("Time: %ld microseconds\n", (endtime.tv_sec - starttime.tv_sec)*1000000 + endtime.tv_usec - starttime.tv_usec);
  
  //printmat(matrix, matwidth);
  free(matrix);
}

void printmat (int* matrix, int width) {
  for (int i = 0; i < width*width; i++) {
    printf ("%d\t",matrix[i]);
    if (i%width == width-1) {
      printf ("\n");
    }
  }
  printf ("\n");
}
