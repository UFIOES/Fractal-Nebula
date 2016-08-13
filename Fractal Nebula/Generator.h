#pragma once

typedef struct nebulaData {
	float x;
	float y;
	float z;
	float color[3];
} nebulaData;

nebulaData* generate();
