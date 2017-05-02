#include <stdio.h>

int is_little() {
  int i = 1;
  char *ptr = (char *) &i;
  if (*ptr == 1) return 1;
  return 0;
}

int main (void) {
  int result = is_little();
  if(result == 1)  printf("\n Resultado: Little Endian");
  else printf("\nResultado: Big Endian");
  return 0;
}
