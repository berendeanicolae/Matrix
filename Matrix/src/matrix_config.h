#ifndef IMATRIX_H
#define IMATRIX_H

#include <cstdint>
#include <string>
using namespace std;

class MatrixConfig {
private:
	static uint32_t step;
	static void handler(char *key, char *value);

public:
	static void init();
	static void init(uint32_t step);
	static void init(string configFilePath);
	static void init(wstring configFilePath);

	static uint32_t getStepSize();
};

#endif //IMATRIX_H
