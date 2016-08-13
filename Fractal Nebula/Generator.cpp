#include "stdafx.h"
#include "Generator.h"

nebulaData* generate() {

	nebulaData* output = new nebulaData[100];

	for (int i = 0; i < 100; i++) {
		output[i].x = 1;
	}

	return output;

}
