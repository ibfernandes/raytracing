#pragma once
#include "Vec3.h"

Vec3<float> seed(0, 0, 0);

float fraction(float f) {
	int v = f;
	return f - float(v);
}

/*
	Returns a random number between [0, 1)
*/
float random() {
	seed = seed + Vec3<float>(1, 1, 1);
	return fraction(sin(seed.dot(Vec3<float>(12.9898, 4.1414, 0))) * 43758.5453) * 0.5f + 0.5f;
}


Vec3<float> sampleUnitSphereUsingRejection() {
	Vec3<float> vec;
	do {
		vec = Vec3<float>(random(), random(), random());
	} while (vec.length() > 1);
	return vec;
}