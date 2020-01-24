#pragma once
#include "Material.h"
#include "Vec3.h"
#include "Math.h"

class DiffuseMaterial : public Material {
public:
	Vec3<float> albedo;

	DiffuseMaterial(Vec3<float> albedo) {
		this->albedo = albedo;
	};

	/*
		Note we could just as well only scatter with some probability p and have attenuation be albedo/p. Your choice. 
	*/
	bool scatter(Ray &rayIn, Hit &hit, Vec3<float> &attenuation, Ray &scattered) {
		Vec3<float> target = hit.p + hit.normal + sampleUnitSphereUsingRejection();
		scattered = Ray(hit.p, target - hit.p);
		attenuation = albedo;
		return true;
	};
};