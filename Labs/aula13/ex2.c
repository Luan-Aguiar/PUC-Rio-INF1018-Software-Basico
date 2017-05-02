#include <stdio.h>
#include <math.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
 } U;

float int2float(int i) {
	U u;
	unsigned int s=0,e = 0,f,temp=i;
		
	if(i == 0) return 0;

	if(i < 0) {
		s = 1;
		temp = -temp;
	}

	while(temp >> e != 1) {
		e++;
	}

	/* para parte fracionário 23 - E quando E < 23, E-23 se E > 23 */
	if(e <= 23) f = temp << (23 - e);
	else f = temp >> (e - 23);

	u.i = makefloat(s,e+127,f);

	return u.f;
}

int main(void) {
	int i;

	printf("\n******** int2float ****************\n");
	i = 0;
	printf(" %d -> %+10.4f\n", i, int2float(i));
	i = 1;  
	printf(" %d -> %+10.4f\n", i, int2float(i));
	i = -1;  
	printf(" %d -> %10.4f\n", i, int2float(i));
	i = 0x7fffffff;  
	printf(" %d -> %+10.4f\n", i, int2float(i));
	i = -i;
	printf(" %d -> %+10.4f\n", i, int2float(i));
	i = 12345;
	printf(" %d -> %+10.4f\n", i, int2float(i));
	i = -12345;
	printf(" %d -> %+10.4f\n", i, int2float(i));
	return 0;
}
