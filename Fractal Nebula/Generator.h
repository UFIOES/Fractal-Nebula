#pragma once

struct nebulaData {
	float x;
	float y;
	float z;
	float color[4];
};

struct variation {
	float weight;
	float x[4];
	float y[4];
	float z[4];
	float color[4];
};

void generate(int iterations, variation* functions, int n, nebulaData* output);
