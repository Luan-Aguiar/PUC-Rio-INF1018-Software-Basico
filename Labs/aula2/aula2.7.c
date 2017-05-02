#include <ctype.h>
#include <stdio.h>

int string2num (char *s, int radix) {
  int a = 0;
  for (; *s; s++) {
   if(isalpha(*s))a = a*radix + ((*s - 'a') + 10);
   else a = a*radix + (*s - '0');
  }
  return a;
}

int main (void) {
  printf("==> %d\n", string2num("1a", 16));
  printf("==> %d\n", string2num("1232", 3));
  printf("==> %d\n", string2num("73", 8));
  printf("==> %d\n", string2num("0001", 2)); // (1) 10
  printf("==> %d\n", string2num("11110001", 2)); // (241) 10
  printf("==> %d\n", string2num("1234", 10) + 1);
  printf("==> %d\n", string2num("1234", 10) + string2num("1", 10));
  return 0;
}
