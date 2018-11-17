#include <stdio.h>
#include <stdlib.h>

void printmat (int* matrix, int width);

int main (int argc, char**argv) {
  if (argc != 3) {
    fprintf(stderr,
	    "Wrong number of command-line arguments\nUsage: %s <Matrix width> <Block width>\n", argv[0]);
    return -1;
  }

  int matwidth = atoi(argv[1]);
  int blockwidth = atoi(argv[2]);

  int* matrix = malloc(matwidth*matwidth*sizeof(int));
  int* block = malloc(blockwidth*blockwidth*sizeof(int));

  for (int i = 0; i < matwidth*matwidth; i++) {
    //matrix[i] = rand();
    matrix[i] = i;
  }

  int tmp;
  printmat(matrix, matwidth);
  for (int i = 0; i < matwidth; i++) {
    for (int j = i+1; j < matwidth; j++) {
      tmp = matrix[i*matwidth + j];
      matrix[i*matwidth + j] = matrix[j*matwidth + i];
      matrix[j*matwidth + i] = tmp;
    }
  }
  printmat(matrix, matwidth);
  free(matrix);
  free(block);
}

void printmat (int* matrix, int width) {
  for (int i = 0; i < width*width; i++) {
    printf ("%d\t",matrix[i]);
    if (i%width == width-1) {
      printf ("\n");
    }
  }
}
