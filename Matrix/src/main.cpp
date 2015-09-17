#include "Matrix.h"

int main()
{
	Matrix a(2, 3), b(3, 2), c(2, 2);

	a.set(0, 0, 1);
	a.set(0, 1, 2);
	a.set(0, 2, 3);
	a.set(1, 0, 4);
	a.set(1, 1, 5);
	a.set(1, 2, 6);

	b.set(0, 0, 1);
	b.set(0, 1, 2);
	b.set(1, 0, 3);
	b.set(1, 1, 4);
	b.set(2, 0, 5);
	b.set(2, 1, 6);

	Matrix::mul(a, b, c);
	return 0;
}