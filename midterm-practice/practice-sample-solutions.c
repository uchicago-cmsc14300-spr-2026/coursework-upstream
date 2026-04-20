#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "practice.h"

double dist(double x1, double y1, double x2, double y2)
{
  double dx = x2-x1;
  double dy = y2-y1;
  return sqrt(dx*dx+dy*dy);
}

double dist_to(double x, double y, double cx, double cy, double r)
{
  double d = r-dist(x,y,cx,cy);
  return d<0?-d:d;
}

int get_bit(uint8_t b, uint64_t n)
{
  return (n>>b)&0X1;
}

uint32_t odd_bits(uint64_t n)
{
  uint32_t current_power_of_two = 1;
  uint32_t result = 0;
  for (int i=1; i<64; i+=2) {
    result += current_power_of_two * ((n>>i)&0X1);
    current_power_of_two *= 2;
  }
  return result;
}

int index_of(char *s, char c)
{
  int len = strlen(s);
  for (int i=0; i<len; i++) {
    if (s[i]==c) {
      return i;
    }
  }
  return -1;
}

char *revcap(char *s)
{
  int len = strlen(s);
  char *t = malloc(len+1);
  t[len] = '\0';
  for (int i=0; i<len; i++) {
    char c = s[len-i-1];
    if ('a'<=c && c<='z') {
      c = 'A'+(c-'a');
    }
    t[i] = c;
  }
  return t;
}

char *until(char *s, char marker)
{
  int marker_pos = -1;
  int i=0;
  while (s[i]!='\0') {
    if (s[i]==marker) {
      marker_pos = i;
      break;
    }
    i++;
  }
  if (marker_pos==-1) {
    return strdup(s);
  }
  char *t = malloc(marker_pos+1);
  for (int i=0; i<marker_pos; i++) {
    t[i] = s[i];
  }
  t[marker_pos] = '\0';
  return t;
}

char *ins(char *s1, char *s2, unsigned int pos)
{
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  char *t = malloc(len1+len2+1);
  t[len1+len2] = '\0';
  if (pos>=len1) {
    for (int i=0; i<len1; i++) 
      t[i] = s1[i];
    for (int i=0; i<len2; i++)
      t[len1+i] = s2[i];
    return t;
  } else {
    for (int i=0; i<pos; i++)
      t[i] = s1[i];
    for (int i=0; i<len2; i++)
      t[pos+i] = s2[i];
    for (int i=0; i<len1-pos; i++)
      t[pos+len2+i] = s1[pos+i];
    return t;
  }
}

int main()
{
  printf("----- sample solutions -----\n");
  // you can try test cases here...
  return 0;
}
