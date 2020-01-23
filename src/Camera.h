#pragma once
#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
	Vec3<float> lowerLeft;
	Vec3<float> horizontal;
	Vec3<float> vertical;
	Vec3<float> origin;

	Camera() {
		lowerLeft = Vec3<float>(-2, -1, -1);
		horizontal = Vec3<float>(4, 0, 0);
		vertical = Vec3<float>(0, 2, 0);
		origin = Vec3<float>(0, 0, 0);
	};

	Ray getRayPassingThrough(float u, float v) {
		return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
	}
};

