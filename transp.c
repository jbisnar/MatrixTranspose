#include <stdio.h>
#include <stdlib.h>

void printmat (int* matrix, int width);
void transmat (int mwidth, int bwidth, int* mat, int* block);
void transblock (int x, int y, int mwidth, int bwidth, int* mat, int* block);

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

  printmat(matrix, matwidth);
  transmat(matwidth, blockwidth, matrix, block);
  free(matrix);
  free(block);
}

void transmat (int mwidth, int bwidth, int* mat, int* block) {
  int redwidth = mwidth / bwidth;
  for (int i = 0; i < redwidth; i++) {
    for (int j = 0; j < redwidth; j++) {
      //printf("(%d, %d)\n", i*bwidth, j*bwidth);
      transblock (j*bwidth, i*bwidth, mwidth, bwidth, mat, block);
    }
  }
}

void transblock (int x, int y, int mwidth, int bwidth, int* mat, int* block) {
  int endx = x+bwidth;
  int endy = y+bwidth;
  int swapwidth;

  for (int i = y; i < endy; i++) {
    for (int j = x; j < endx; j++) {
      block[(i-y)*bwidth+(j-x)] = mat[i*mwidth+j];
    }
  }
  printmat(block, bwidth);
  printf("\n");
}

void printmat (int* matrix, int width) {
  for (int i = 0; i < width*width; i++) {
    printf ("%d\t",matrix[i]);
    if (i%width == width-1) {
      printf ("\n");
    }
  }
}
