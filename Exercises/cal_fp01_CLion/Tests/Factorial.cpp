/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n) {
    if (n == 0 || n == 1)
        return 1;

	return n * factorialRecurs(n -1);
}

int factorialDinam(int n) {
	int result = n;
	int n_copy = n;

    for (int i = 1; i < n; i++) {
        n_copy--;
        result *= n_copy;
	}

    return result;
}
