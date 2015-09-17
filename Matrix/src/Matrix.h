#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>

//template <class T>
class Matrix {
private:
	double *data;
	uint32_t _rows, _cols;
public:
	Matrix() : _rows(0), _cols(0), data(0) {}
	Matrix(uint32_t rows, uint32_t cols) : _rows(0), _cols(0), data(0) {
		if (rows && cols) {
			data = new double[rows*cols]();
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

	void set(uint32_t row, uint32_t column, double value) {
		data[row*_cols + column] = value;
	}

	double get(uint32_t row, uint32_t column) {
		return data[row*_cols + column];
	}
public:
	static void mul(Matrix& a, Matrix& b, Matrix& c) {
		//TODO: transpose
		for (uint32_t i = 0; i < a._rows; ++i) {
			for (uint32_t j = 0; j < b._cols; ++j) {
				for (uint32_t k = 0; k < a._cols; ++k) {
					c.data[i*c._cols + j] += a.data[i*a._cols + k] * b.data[k*b._cols + j];
				}
			}
		}
	}
};

#endif //MATRIX_H
