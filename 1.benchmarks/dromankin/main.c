
#include <inttypes.h>

double fmadd (double a, double b, double c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
		a += b * c;
	}
	return a;
}

double fmsub (double a, double b, double c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
		a = a - b * c;
	}
	return a;
}

double fmsub4 (double d, double a, double b, double c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
		d += a + b * c;
	}
	return d;
}

double fmadd4 (double d, double a, double b, double c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
		d -= a + b * c;
	}
	return d;
}



int main() {
	double a, b, c, d;
	a = 4.0f;
	b = 1.5f;
	c = 2.4f;
	d = 8.999f;
	//a = fmsub4(d, a, b, c);/
	//a = fmsub(a, b, c);
	//for (int32_t i = 0; i < N; i++) {
	a = fmadd(a, b, c);
	//}
	//d = fmsub4(d, a, b, c);
	return 0;
}
