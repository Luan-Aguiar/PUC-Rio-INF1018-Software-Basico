#include <stdio.h>

unsigned char switch_byte(unsigned char x) {
  return (x << 4) | (x >> 4);
}

unsigned char rotate_left(unsigned char x, int n) {
  return (x << n) | (x >> (8-n));
}

int main(void) {
  printf("switch_byte / 0xBA: %0x\n", switch_byte(0xBA));  // Deve retornar 0xAB
  
  printf("rotate_left / 0x61 - 1 bit: 0x%0x\n", rotate_left(0x61, 1));  // Deve retornar 0xc2
  printf("rotate_left / 0x61 - 2 bit: 0x%0x\n", rotate_left(0x61, 2));  // Deve retornar 0x85
  printf("rotate_left / 0x61 - 7 bit: 0x%0x\n", rotate_left(0x61, 7));  // Deve retornar 0xb0
  
  return 0;
}
