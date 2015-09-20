#include "matrix_config.h"
#include "matrix_primitives.h"
#include "config_reader.h"

#define TEST_SIZE 1024

uint32_t MatrixConfig::step = 0;

void MatrixConfig::handler(char *key, char *value) {
	if (!strcmp(key, "step")) {
		step = atoi(value);
	}
}

#ifdef _WIN32
#include <Windows.h>

uint32_t getTicks() {
	return GetTickCount();
}
#endif

#ifdef __unix__
#include <ctime>
uint32_t getTicks() {
	timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec*1000+ts.tv_nsec/1000000;
}
#endif

void MatrixConfig::init() {
	if (!step) {
		double *a, *c;
		uint32_t start, end, bestTime;

		a = new double[TEST_SIZE*TEST_SIZE];
		c = new double[TEST_SIZE*TEST_SIZE];

		step = 8;
		start = getTicks();
		MatrixPrimitives::ijkmul(TEST_SIZE, TEST_SIZE, TEST_SIZE, a, a, c, step);
		end = getTicks();
		bestTime = end - start;

		for (uint32_t i = 16; i <= 1024; i *= 2) {
			start = getTicks();
			MatrixPrimitives::ijkmul(TEST_SIZE, TEST_SIZE, TEST_SIZE, a, a, c, 8);
			end = getTicks();
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
