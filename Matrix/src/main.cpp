#include "Matrix.h"
#include <cstdio>
#include <Windows.h>
#define SIZE 2048
#define IT 10
int main()
{
	Matrix a(SIZE, SIZE, false), b(SIZE, SIZE, false), c(SIZE, SIZE, false);

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			a.set(i, j, 1);
			b.set(i, j, 1);
		}
	
	DWORD time = 0;
	printf("cachemul:\n");
	for (int i = 2; i <= 1024; i<<=1) {
		c.reset();
		DWORD start = GetTickCount();
		Matrix::ikjmul2(a, a, c);
		DWORD end = GetTickCount();
		time += end - start;
		printf("\t%d: %d.%d\n", i, (end - start) / 1000, (end - start) % 1000);
	}
	time /= IT;
	printf("\tavg=%d.%d\n", time / 1000, time % 1000);

	/*Matrix::optmul(a, b, c);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			printf("%g ", c.get(i, j));
		}
		puts("");
	}*/
	//MatrixConfig::__init__();
	return 0;
}