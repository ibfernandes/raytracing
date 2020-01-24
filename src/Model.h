#pragma once
#include "Ray.h"
#include "Vec3.h"

class Material;

struct Hit {
	float t;
	Vec3<float> p;
	Vec3<float> normal;
	Material *material;
};

class Model {
public:
	virtual bool hit(Ray &r, float tMin, float tMax, Hit &hit) = 0;
};