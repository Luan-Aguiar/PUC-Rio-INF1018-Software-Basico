#include <stdio.h>

typedef int (*funcp) (int x);

int add (int x) {
  return x+1;
}

int main(void) {
	int i;
	unsigned char codigo[] = {0x55,0x89,0xe5,0xff,0x75,0x08,0xe8,0xfc,0xff,0xff,0xff,0x89, 0xec, 0x5d, 0xc3};
	int tmp = (int)&add - (int)&codigo[11];
	unsigned char *tmp2 = (unsigned char *)&tmp;

	codigo[7] = tmp2[0];
	codigo[8] = tmp2[1];
	codigo[9] = tmp2[2];
	codigo[10] = tmp2[3];

	funcp f = (funcp)codigo;
	i = (*f)(10);
	printf("%d\n", i);
	return 0;
}
