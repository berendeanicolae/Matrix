#ifndef IMATRIX_H
#define IMATRIX_H

#include <cstdint>

class IMatrix {
private:
	static bool initializied;
	static uint32_t cacheLineSize;

private:
	static void init();

protected:
	static uint32_t getCaheLineSize();
};

#endif //IMATRIX_H
