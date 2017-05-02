#include <stdio.h>

int add1 (int *a, int n);

int main (void) {
   int a[3] = {1,2,3};
   printf("%d\n", add1(a, 3));
   return 0;
}

