#pragma once
#include "Material.h"
#include "Math.h"

class MetalMaterial : public Material {
public:
	Vec3<float> albedo;

	MetalMaterial(Vec3<float> albedo) {
		this->albedo = albedo;
	};

	/*
		NOTE: we could just as well only scatter with some probability p and have attenuation be albedo/p.
	*/
	bool scatter(Ray &rayIn, Hit &hit, Vec3<float> &attenuation, Ray &scattered) {
		Vec3<float> target = hit.p + hit.normal + sampleUnitSphere();
		Vec3<float> reflected = reflect(rayIn.direction.normalize(), hit.normal);
		scattered = Ray(hit.p, reflected);
		attenuation = albedo;
		return (scattered.direction.dot(hit.normal) > 0);
	};
};