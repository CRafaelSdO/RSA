#include "libs/prime_numbers.h"

bool is_it_prime(s64_t n) {
	if(n < 2 || (n != 2 && n % 2 == 0) || (n != 3 && n % 3 == 0)) {
		return false;
	} else {
		int increment = 4;

		for(s64_t i = 5; i * i <= n; i += increment) {
			if(n % i == 0) {
				return false;
			} else {
				increment = 6 - increment;
			}
		}

		return true;
	}
}

bool are_they_co_primes(s64_t n, s64_t m) {
	if(m == 0) {
		return n == 1;
	} else {
		return are_they_co_primes(m, n % m);
	}
}