#include <math.h>
#include <stdio.h>

float foo1 (float a, float b);

int main(void) {
	printf("Result: %f\n", foo1(M_PI, 2.1)); ///2.1
	printf("Result: %f", foo1(M_PI_2, 5.5)); //6.5
	return 0;
}
