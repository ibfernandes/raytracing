#pragma once
#include "Model.h"
#include "Vec3.h"
#include "Material.h"

class Sphere : public Model {
public:
	Vec3<float> center;
	float radius;
	Material *material;

	Sphere(Vec3<float> center, float radius) {
		this->center = center;
		this->radius = radius;
	};

	Sphere(Vec3<float> center, float radius, Material *material) {
		this->center = center;
		this->radius = radius;
		this->material = material;
	};

	/*
		Sphere equation in vector form.
	*/
	inline bool hit(Ray &r, float tMin, float tMax, Hit &hit) {
		Vec3<float> oc = r.origin - center;
		float a = r.direction.dot(r.direction);
		float b = oc.dot(r.direction);
		float c = oc.dot(oc) - radius * radius;
		float discriminant = b * b - a * c;

		if (discriminant >= 0) {
			float temp = (-b - sqrt(discriminant)) / a;
			if (temp > tMin && temp < tMax) {
				hit.t = temp;
				hit.p = r.getPointAt(hit.t);
				hit.normal = ((hit.p - center) / radius).normalize();
				hit.material = material;
				return true;
			}

			temp = (-b + sqrt(discriminant)) / a;
			if (temp > tMin && temp < tMax) {
				hit.t = temp;
				hit.p = r.getPointAt(hit.t);
				hit.normal = ((hit.p - center) / radius).normalize();
				hit.material = material;
				return true;
			}
		}

		return false;
	}
};