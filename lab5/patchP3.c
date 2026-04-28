#include <stdlib.h>
#include <stdio.h>

// Generates a P3 image in a soothing shade of blue.

int main(int argc, char *argv[])
{
  if (argc!=3) {
    fprintf(stderr,"Please supply width and height.\n");
    exit(1);
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  printf("P3\n%d %d\n255\n",width,height);
  for (int i=0; i<width*height; i++)
    printf("0 0 128\n");
  return 0;
}

