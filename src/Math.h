#pragma once
#include "Vec3.h"
#define PI 3.14159265358979323846264338327950288

Vec3<float> seed(0, 0, 0);

/*
	Receives an angle in degrees and returns its conversion to radians.
*/
float radians(float angleInDregrees) {
	return angleInDregrees * PI / 180.0f;
}

float fraction(float f) {
	int v = f;
	return f - float(v);
}

/*
	Returns a random number between [0, 1)
*/
//NOTE: Missing mod.
float random() {
	seed = seed + Vec3<float>(1, 1, 1);
	return fraction(sin(seed.dot(Vec3<float>(12.9898, 4.1414, 0))) * 43758.5453) * 0.5f + 0.5f;
}

Vec3<float> sampleUnitSphere() {
	float theta = 2 * PI * random();
	float phi = acos(1 - 2 * random());
	return Vec3<float>(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}


Vec3<float> sampleUnitSphereUsingRejection() {
	Vec3<float> vec;
	do {
		vec = 2.0f * Vec3<float>(random(), random(), random()) - Vec3<float>(1, 1, 1);
	} while (vec.squaredLength() >= 1);
	return vec;
}

Vec3<float> randomInUnitDisk() {
	Vec3<float> vec;
	do {
		vec = 2.0f * Vec3<float>(random(), random(), 0) - Vec3<float>(1, 1, 0);
	} while (vec.squaredLength() >= 1);
	return vec;
}