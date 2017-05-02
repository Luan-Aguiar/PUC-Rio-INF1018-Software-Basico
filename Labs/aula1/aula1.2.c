#include <stdio.h>
#include <stdlib.h>

float foo (float pf);

int bar (int pb);

int main (int argc, char **argv) {
  int i; float f;
  if(argc != 3) {
    printf ("uso do programa: %s <int> <float> \n", argv[0]);
    exit(0);
  }
  i = atoi(argv[1]);
  f = atof(argv[2]);
  printf ("bar(%d): %d \nfoo(%.2f): %.2f\n",
        i, bar(i), f, foo(f));
  return 0;
}
