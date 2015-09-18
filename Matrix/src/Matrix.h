#ifndef MATRIX_H
#define MATRIX_H

#include "IMatrix.h"
#include <cstring>
#include <emmintrin.h>

//template <class T>
class Matrix : public IMatrix {
private:
	double *data;
	uint32_t _rows, _cols;

public:
	Matrix() : _rows(0), _cols(0), data(0) {}
	Matrix(uint32_t rows, uint32_t cols, bool init=true) : _rows(0), _cols(0), data(0) {
		if (rows && cols) {
			if (init) data = new double[rows*cols]();
			else data = new double[rows*cols];
			if (data) {
				_rows = rows;
				_cols = cols;
			}
		}
	}
	~Matrix() {
		if (data)
			delete[] data;
		data = 0;
		_rows = _cols = 0;
	}

	void reset() { memset(data, 0, _rows*_cols); }
	void set(uint32_t row, uint32_t column, double value) { data[row*_cols + column] = value; }
	double get(uint32_t row, uint32_t column) { return data[row*_cols + column]; }

public:
	static void add(Matrix& a, Matrix& b, Matrix& c) {
		double *a2, *b2, *c2, *end;


		for (a2 = a.data, b2 = b.data, c2 = c.data, end = a.data + a._rows*a._cols; a2 < end; ++a2, ++b2, ++c2) {
			*a2 = *b2 + *c2;
		}
	}

	static void ikjmul(Matrix& a, Matrix& b, Matrix& c) {
		for (uint32_t i = 0; i < a._rows; ++i) {
			for (uint32_t k = 0; k < b._cols; ++k) {
				for (uint32_t j = 0; j < a._cols; ++j) {
					c.data[i*c._cols + j] += a.data[i*a._cols + k] * b.data[k*b._cols + j];
				}
			}
		}

	}

	static void ikjmul2(Matrix& a, Matrix& b, Matrix& c) {
		uint32_t i, k, j;
		double *a2, *b2, *c2;

		for (i = 0, a2 = a.data, c2 = c.data; i < a._rows; ++i, a2 += a._cols, c2 += c._cols) {
			for (k = 0, b2=&b.data[k*b._cols]; k < b._rows; ++k, b2+=b._cols) {
				for (j = 0; j < b._cols; ++j) {
					c2[j] += a2[k] * b2[j];
				}
			}
		}
	}

	static void cachemul(Matrix& a, Matrix& b, Matrix& c, uint32_t step) { //minimum at 256
		//uint32_t step = 32;
		uint32_t i, j, k, i2, j2, k2;
		double *__restrict a2, *__restrict b2, *__restrict c2;

		for (i = 0; i < a._rows; i += step) {
			for (j = 0; j < b._cols; j += step) {
				for (k = 0; k < a._cols; k += step) {
					for (i2 = 0, c2 = &c.data[i*c._cols + j], a2 = &a.data[i*a._cols + k]; i2 < step; ++i2, c2 += c._cols, a2 += a._cols) {
						for (k2 = 0, b2 = &b.data[k*b._cols+j]; k2 < step; ++k2, b2 += b._cols) {
							for (j2 = 0; j2 < step; j2 += 2) {
								c2[j2] += a2[k2] * b2[j2];
							}
						}
					}
				}
			}
		}
	}

	static void cachemulsse(Matrix& a, Matrix& b, Matrix& c, uint32_t step) {
		//uint32_t step = 32;
		uint32_t i, j, k, i2, j2, k2;
		double *__restrict a2, *__restrict b2, *__restrict c2;

		for (i = 0; i < a._rows; i += step) {
			for (j = 0; j < b._cols; j += step) {
				for (k = 0; k < a._cols; k += step) {
					for (i2 = 0, c2 = &c.data[i*c._cols + j], a2 = &a.data[i*a._cols + k]; i2 < step; ++i2, c2 += c._cols, a2 += a._cols) {
						for (k2 = 0, b2 = &b.data[k*b._cols + j]; k2 < step; ++k2, b2 += b._cols) {
							__m128d m1d = _mm_load_sd(&a2[k2]);
							m1d = _mm_unpacklo_pd(m1d, m1d);
							for (j2 = 0; j2 < step; j2 += 2) {
								__m128d m2 = _mm_load_pd(&b2[j2]);
								__m128d r2 = _mm_load_pd(&c2[j2]);
								_mm_store_pd(&c2[j2], _mm_add_pd(_mm_mul_pd(m2, m1d), r2));
							}
						}					}
				}
			}
		}
	}
};

#endif //MATRIX_H
