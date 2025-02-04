
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>





double fmadd (volatile double d, double a, double b, double c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
		d = a + b * c;
	}
	return d;
}

double fmsub (double d, double a, double b, double c) {
	int32_t m = 1000000000;
	for (int32_t i = 0; i < m; i++) {
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;
		d = a - b * c;

	}
	return d;
}



int main(int argc, char** argv) {
	if (argc != 2) {
		printf("usage: main 1-fmadd; 2 = fmsub; 3 = fmadd4; 4 = fmsub4\n");
		exit(1);
	}
	
	int32_t arg = 0;
	arg = atoi(argv[1]);
	double a, b, c, d;
	a = 4.0f;
	b = 1.5f;
	c = 2.4f;
	d = 8.999f;

	switch(arg) {
		case 1: a = fmadd(a, b, c); break;
		case 2: a = fmsub(a, b, c); break;
	}
	
	return 0;
}
