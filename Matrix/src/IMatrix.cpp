#include "IMatrix.h"

#ifdef _WIN32
#include <Windows.h>
#endif

bool IMatrix::initializied = 0;
uint32_t IMatrix::cacheLineSize = 0;

void IMatrix::init() {	
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION *plpi = NULL;
	DWORD size = 0;

	GetLogicalProcessorInformation(plpi, &size);
	plpi = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)];
	GetLogicalProcessorInformation(plpi, &size);
	for (DWORD tr = 0, length = size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); tr < length; ++tr) {
		if (plpi[tr].Relationship == RelationCache && plpi[tr].Cache.Level == 1) {
			cacheLineSize = plpi[tr].Cache.LineSize;
		}
	}
	initializied = 1;

	delete[] plpi;
}

uint32_t IMatrix::getCaheLineSize() {
	if (initializied) {
		return cacheLineSize;
	}

	init();
	return cacheLineSize;
}
