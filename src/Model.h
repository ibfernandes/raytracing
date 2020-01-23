#pragma once
#include "Ray.h"
#include "Vec3.h"

struct Hit {
	float t;
	Vec3<float> p;
	Vec3<float> normal;
};

class Model {
public:
	//Model();

	virtual bool hit(Ray &r, float tMin, float tMax, Hit &hit) = 0;
};