#pragma once
#include "Material.h"
#include "Math.h"

class MetalMaterial : public Material {
public:
	Vec3<float> albedo;

	MetalMaterial(Vec3<float> albedo) {
		this->albedo = albedo;
	};

	Vec3<float> reflect(Vec3<float> &v, Vec3<float> &n) {
		return v - (2.0f * v.dot(n) * n);
	}

	/*
		NOTE: we could just as well only scatter with some probability p and have attenuation be albedo/p.
	*/
	bool scatter(Ray &rayIn, Hit &hit, Vec3<float> &attenuation, Ray &scattered) {
		Vec3<float> target = hit.p + hit.normal + sampleUnitSphereUsingRejection();
		Vec3<float> reflected = reflect(rayIn.direction.normalize(), hit.normal);
		scattered = Ray(hit.p, reflected);
		attenuation = albedo;
		return (scattered.direction.dot(hit.normal) > 0);
	};
};