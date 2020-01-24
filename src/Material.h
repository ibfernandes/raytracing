#pragma once
#include "Ray.h"
#include "Model.h"

class Material {
public:
	float schlick(float cos, float refractionIndex) {
		float r0 = (1 - refractionIndex) / (1 + refractionIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cos), 5);
	}

	Vec3<float> reflect(Vec3<float> &v, Vec3<float> &n) {
		return v - (2.0f * v.dot(n) * n);
	}
	
	bool refract(Vec3<float> &v, Vec3<float> &n, float ni, Vec3<float> &refracted) {
		Vec3<float> uv = v.normalize();
		float d = uv.dot(n);
		float discriminant = 1.0f - ni * ni * (1 - d * d);
		if (discriminant > 0) {
			refracted = ni * (uv - n * d) - n * sqrt(discriminant);
			return true;
		}
		else
			return false;
	}

	virtual bool scatter(Ray &rayIn, Hit &hit, Vec3<float> &attenuation, Ray &scattered) = 0;
};