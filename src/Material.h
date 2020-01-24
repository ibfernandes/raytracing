#pragma once
#include "Ray.h"
#include "Model.h"

class Material {
public:
	virtual bool scatter(Ray &rayIn, Hit &hit, Vec3<float> &attenuation, Ray &scattered) = 0;
};