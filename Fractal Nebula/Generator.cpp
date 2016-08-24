#include "stdafx.h"
#include "Generator.h"

void generate(int iterations, variation* functions, int n, nebulaData* output) {

	std::mt19937 engine(time(NULL));

	float weightSum = 0;

	for (int i = 0; i < n; i++) {
		weightSum += functions[i].weight;
	}

	std::uniform_real_distribution<float> picker(0, weightSum);
	std::uniform_real_distribution<float> point(-1.0f, 1.0f);
	std::uniform_real_distribution<float> color(0.0f, 1.0f);

	nebulaData state = {
		point(engine), point(engine), point(engine),
		color(engine), color(engine), color(engine), 1.0f,
	};

	for (int i = -20; i < iterations; i++) {

		float pick = picker(engine);

		int choice = 0;

		for (; choice < n && pick > 0; choice++) {
			pick -= functions[choice].weight;
		}

		float tx, ty, tz;

		tx = functions[choice].x[0] + functions[choice].x[1] * state.x + functions[choice].x[2] * state.y + functions[choice].x[3] * state.z;
		ty = functions[choice].y[0] + functions[choice].y[1] * state.x + functions[choice].y[2] * state.y + functions[choice].y[3] * state.z;
		tz = functions[choice].z[0] + functions[choice].z[1] * state.x + functions[choice].z[2] * state.y + functions[choice].z[3] * state.z;

		for (int j = 0; j < 3; j++) {
			state.color[j] = powf((powf(state.color[j], 2.0f) + powf(functions[choice].color[j], 2.0f)) / 2.0f, 0.5f);
		}

		state.x = tx / (powf(tx, 2.0f) + powf(ty, 2.0f) + powf(tz, 2.0f));
		state.y = ty / (powf(tx, 2.0f) + powf(ty, 2.0f) + powf(tz, 2.0f));
		state.z = tz / (powf(tx, 2.0f) + powf(ty, 2.0f) + powf(tz, 2.0f));

		if (i >= 0) {
			output[i] = state;
		}

	}

}
