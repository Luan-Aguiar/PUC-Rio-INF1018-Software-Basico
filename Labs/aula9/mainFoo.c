#include <stdio.h>

void foo (int a[], int n);

void dumpVetor(int a[], int n) {
  int i;
  for(i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main(void) {
  int vet[8] = {6,2,0,1,2,0,50,0};
  dumpVetor(vet, 8);
  foo(vet, 8);
  dumpVetor(vet, 8);
  return 0;
}
