#ifndef MATRIX_PRIMITIVES_H
#define MATRIX_PRIMITIVES_H

#include <cstdint>

namespace MatrixPrimitives {
	void add(uint32_t n, uint32_t m, double *a, double *b, double *c);
	void add(uint32_t n, uint32_t m, double *a, uint32_t lda, double *b, uint32_t ldb, double *c, uint32_t ldc);
	void ikjmul(uint32_t n, uint32_t m, uint32_t l, double *a, double *b, double *c);
	void ikjmul(uint32_t n, uint32_t m, uint32_t l, double *a, uint32_t lda, double *b, uint32_t ldb, double *c, uint32_t ldc);
	//only use if step divides n, m and l
	void ijkmul(uint32_t n, uint32_t m, uint32_t l, double *a, double *b, double *c, uint32_t step);
	//only use if step divides n, m and l
	void ijkmulsse(uint32_t n, uint32_t m, uint32_t l, double *a, double *b, double *c, uint32_t step);
}

#endif //MATRIX_PRIMITIVES_H
