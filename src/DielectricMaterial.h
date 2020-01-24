#pragma once
#include "Material.h"

class DielectricMaterial: public Material {
public:
	float refractionIndex;

	DielectricMaterial(float refractionIndex) {
		this->refractionIndex = refractionIndex;
	}

	bool scatter(Ray &rayIn, Hit &hit, Vec3<float> &attenuation, Ray &scattered) {
		Vec3<float> outwardNormal;
		Vec3<float> refracted;
		Vec3<float> reflected = reflect(rayIn.direction, hit.normal);
		float rIndex;
		attenuation = Vec3<float>(1, 1, 1);

		float cos;
		float reflectProb;

		//if rayIn and normal are not perpendicullar
		if (rayIn.direction.dot(hit.normal) > 0) {
			outwardNormal = -hit.normal;
			rIndex = refractionIndex;
			cos = refractionIndex * rayIn.direction.dot(hit.normal) / rayIn.direction.length();
		}else {
			outwardNormal = hit.normal;
			rIndex = 1.0f/ refractionIndex;
			cos = - rayIn.direction.dot(hit.normal) / rayIn.direction.length();
		}

		if (refract(rayIn.direction, outwardNormal, rIndex, refracted)) 
			reflectProb = schlick(cos, refractionIndex);
		else
			reflectProb = 1.0f;

		if (random() < reflectProb)
			scattered = Ray(hit.p, reflected);
		else
			scattered = Ray(hit.p, refracted);

		return true;
	}
};