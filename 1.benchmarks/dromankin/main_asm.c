#include <inttypes.h>

float fmadd(float d, float a, float b, float c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
	asm volatile(
		"fmadd.s %0, %1, %2, %3"
		: "=f"(d)
		: "f"(b), "f"(c)  , "f"(a)
	);
	}
	return d;
}


float fmsub(float d, float a, float b, float c) {
	int32_t m = 100000000;
	for (int32_t i = 0; i < m; i++) {
	asm volatile(
		"fmsub.s %0, %1, %2, %3"
		: "=f"(d)
		: "f"(b), "f"(c)  , "f"(a)
	);
	}
	return d;
}

int main() {
	float a = 3.0f;
	float b = 2.0f;
	float c = 4.0f;
	float d = 0.0f;
	d = fmsub(d, a, b, c);
	return 0;
}
