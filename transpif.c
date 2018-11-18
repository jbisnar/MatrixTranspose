#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void printmat (int* matrix, int width, int height);

int main (int argc, char**argv) {
  if (argc != 4) {
    fprintf(stderr,
	    "Wrong number of command-line arguments\nUsage: %s <Matrix width> <Matrix height> <Block width>\n", argv[0]);
    return -1;
  }

  int matwidth = atoi(argv[1]);
  int matheight = atoi(argv[2]);
  int blockwidth = atoi(argv[3]);
  if (blockwidth < 1) {
    printf("Invalid block width being replaced with 1\n");
    blockwidth = 1;
  }

  int* matrix = malloc(matwidth*matheight*sizeof(int));
  int* trans = malloc(matwidth*matheight*sizeof(int));

  for (int i = 0; i < matwidth*matheight; i++) {
    //matrix[i] = rand();
    matrix[i] = i;
  }

  struct timeval starttime;
  gettimeofday(&starttime, NULL);
  
  int tmp;
  printmat(matrix, matwidth, matheight);
  for (int i = 0; i < matheight; i += blockwidth) {
    for (int j = 0; j < matwidth; j += blockwidth) {
      for (int k = 0; k < blockwidth; k++) {
	for (int l = 0; l < blockwidth; l++) {
	  if ((i+k) < matheight && (j+l) < matwidth) {
	    printf("Transposing (%d,%d) to (%d,%d)\n",(j+l),(i+k),(i+k),(j+l));
	    trans[(j+l)*matheight+(i+k)] = matrix[(i+k)*matwidth+(j+l)];
	  }
	}
      }
      /*
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
      */
    }
  }
  struct timeval endtime;
  gettimeofday(&endtime, NULL);
  printf("Time: %ld microseconds\n", (endtime.tv_sec - starttime.tv_sec)*1000000 + endtime.tv_usec - starttime.tv_usec);
  
  printmat(trans, matheight, matwidth);
  free(matrix);
}

void printmat (int* matrix, int width, int height) {
  for (int i = 0; i < width*height; i++) {
    printf ("%d\t",matrix[i]);
    if (i%width == width-1) {
      printf ("\n");
    }
  }
  printf ("\n");
}
