/*
 *	
 * The tiled versions were What Every Programmer Should Know About Memory
	https://people.freebsd.org/~lstewart/articles/cpumemory.pdf
 *
 *
 *
 */


#include "matrix_primitives.h"
#include <emmintrin.h>


void add(uint32_t n, uint32_t m, double *a, double *b, double *c) {
	uint32_t i, size;

	for (i = 0, size = n*m; i < size; ++i)
		c[i] = a[i] + b[i];
}

void add(uint32_t n, uint32_t m, double *a, uint32_t lda, double *b, uint32_t ldb, double *c, uint32_t ldc) {
	uint32_t i, j;

	for (i = 0; i < n; ++i, a += lda, b += ldb, c += ldc) {
		for (j = 0; j < m; ++j) {
			c[j] = a[j] + b[j];
		}
	}
}

void ikjmul(uint32_t n, uint32_t m, uint32_t l, double *a, double *b, double *c) {
	uint32_t i, k, j;

	for (i = 0; i < n; ++i, a += m, c += l) {
		for (k = 0; k < m; ++k, b += l) {
			for (j = 0; j < l; ++j) {
				c[j] += a[k] * b[j];
			}
		}
	}
}

void ikjmul(uint32_t n, uint32_t m, uint32_t l, double *a, uint32_t lda, double *b, uint32_t ldb, double *c, uint32_t ldc) {
	uint32_t i, k, j;

	for (i = 0; i < n; ++i, a += lda, c += ldc) {
		for (k = 0; k < m; ++k, b += ldb) {
			for (j = 0; j < l; ++j) {
				c[j] += a[k] * b[j];
			}
		}
	}
}

void ijkmul(uint32_t n, uint32_t m, uint32_t l, double *a, double *b, double *c, uint32_t step) {
	uint32_t i, j, k, i2, j2, k2;
	double *__restrict a2, *__restrict b2, *__restrict c2;

	for (i = 0; i < n; i += step) {
		for (j = 0; j < l; j += step) {
			for (k = 0; k < m; k += step) {
				for (i2 = 0, c2 = &c[i*l + j], a2 = &a[i*m + k]; i2 < step; ++i2, c2 += l, a2 += m) {
					for (k2 = 0, b2 = &b[k*l + j]; k2 < step; ++k2, b2 += l) {
						for (j2 = 0; j2 < step; j2 += 2) {
							c2[j2] += a2[k2] * b2[j2];
						}
					}
				}
			}
		}
	}
}

void ijkmulsse(uint32_t n, uint32_t m, uint32_t l, double *a, double *b, double *c, uint32_t step) {
	uint32_t i, j, k, i2, j2, k2;
	double *__restrict a2, *__restrict b2, *__restrict c2;

	for (i = 0; i < n; i += step) {
		for (j = 0; j < l; j += step) {
			for (k = 0; k < m; k += step) {
				for (i2 = 0, c2 = &c[i*l + j], a2 = &a[i*m + k]; i2 < step; ++i2, c2 += l, a2 += m) {
					for (k2 = 0, b2 = &b[k*l + j]; k2 < step; ++k2, b2 += l) {
						__m128d m1d = _mm_load_sd(&a2[k2]);
						m1d = _mm_unpacklo_pd(m1d, m1d);
						for (j2 = 0; j2 < step; j2 += 2) {
							__m128d m2 = _mm_load_pd(&b2[j2]);
							__m128d r2 = _mm_load_pd(&c2[j2]);
							_mm_store_pd(&c2[j2], _mm_add_pd(_mm_mul_pd(m2, m1d), r2));
						}
					}
				}
			}
		}
	}
}
