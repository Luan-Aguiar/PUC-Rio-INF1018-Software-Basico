#include <stdio.h>

// Ímpar - LSB ligado

int odd_ones(unsigned int x) {
  int count = 0;
  
  while(x) {
    if(x & 0x01) count++;
    x = x >> 1;
  }

  return count & 0x01;
}

int main(void) {
  int even = 0x01010101;
  int odd = 0x01030101;
  
  printf("0x01010101: %d\n", odd_ones(even)); // 0
  printf("0x01030101: %d\n", odd_ones(odd)); // 1

  return 0;
}
