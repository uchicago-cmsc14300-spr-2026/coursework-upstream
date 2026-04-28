#include <stdlib.h>
#include <stdio.h>

// Generates a P6 image in a pleasant shade of pale yellow.

int main(int argc, char *argv[])
{
  if (argc!=3) {
    fprintf(stderr,"Please supply width and height.\n");
    exit(1);
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  printf("P6\n%d %d\n255\n",width,height);
  for (int i=0; i<width*height; i++) {
    putchar(255);
    putchar(250);
    putchar(205);
  }
  return 0;
}

