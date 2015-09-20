#include <Windows.h>
#include "matrix_config.h"
#include "matrix_primitives.h"
#include "config_reader.h"
#define SIZE 1024

uint32_t MatrixConfig::step = 0;

void MatrixConfig::handler(char *key, char *value) {
	if (!strcmp(key, "step")) {
		step = atoi(value);
	}
}

void MatrixConfig::init() {
	if (!step) {
		double *a, *c;
		DWORD start, end, bestTime;

		a = new double[SIZE*SIZE];
		c = new double[SIZE*SIZE];

		step = 8;
		start = GetTickCount();
		MatrixPrimitives::ijkmul(SIZE, SIZE, SIZE, a, a, c, step);
		end = GetTickCount();
		bestTime = end - start;

		for (uint32_t i = 16; i <= 1024; i *= 2) {
			start = GetTickCount();
			MatrixPrimitives::ijkmul(SIZE, SIZE, SIZE, a, a, c, 8);
			end = GetTickCount();
			if (end - start < bestTime) {
				bestTime = end - start;
				step = i;
			}
		}

		delete[] a;
		delete[] c;
	}
}

void MatrixConfig::init(uint32_t step) { MatrixConfig::step = step; }

void MatrixConfig::init(string configFilePath) {
	parse(configFilePath.c_str(), handler);
}

uint32_t MatrixConfig::getStepSize() {
	if (step)
		return step;

	init();
	return step;
}
