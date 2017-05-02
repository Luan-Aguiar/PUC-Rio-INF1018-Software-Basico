#include <math.h>
#include <stdio.h>

double foo2 (float a, float b);

int main(void) {
	printf("Result: %f\n", foo2(M_PI, 2.1)); ///-0.504846
	printf("Result: %f", foo2(M_PI_2, 5.5)); //1.708670
	return 0;
}
