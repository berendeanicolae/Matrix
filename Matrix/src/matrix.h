#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <emmintrin.h>
#include "matrix_config.h"
#include "matrix_primitives.h"

class Matrix : public MatrixConfig {
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
		MatrixPrimitives::add(a._rows, a._cols, a.data, b.data, c.data);
	}

	static void ikjmul(Matrix& a, Matrix& b, Matrix& c) {
		MatrixPrimitives::ikjmul(a._rows, a._cols, b._cols, a.data, b.data, c.data);
	}

	static void ijkmul(Matrix& a, Matrix& b, Matrix& c) {
		MatrixPrimitives::ijkmul(a._rows, a._cols, b._cols, a.data, b.data, c.data, getStepSize());
	}

	static void cachemulsse(Matrix& a, Matrix& b, Matrix& c) {
		MatrixPrimitives::ijkmulsse(a._rows, a._cols, b._cols, a.data, b.data, c.data, getStepSize());
	}
};

#endif //MATRIX_H
