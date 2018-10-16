#include "libs/mod_func.h"

S64_t modular_pow(S64_t b, S64_t e, S64_t m) {
	S64_t r = b;
	for(S64_t i = 2; i <= e; i++) {
		r *= b;
		if(r > m) {
			r = r % m;
		}
	}
	return r;
}

S64_t modular_inverse(S64_t a, S64_t m) {
	if(m < 0) {
		m = -m;
	}
	if(a < 0) {
		a = m - (-a % m);
	}
	if(m == 1) {
		return 0;
	} else if(are_they_co_primes(a, m)) {
		S64_t i = 1;
		while((a * i - 1) % m != 0) {
			i++;
		}
		return i;
	} else {
		return -1;
	}
}