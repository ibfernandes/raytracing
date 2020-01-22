#pragma once
#include "Vec3.h"

class Ray {
public:
	union { Vec3<float> o, origin;  };
	union { Vec3<float> d, direction;  };

	Vec3<float> getPointAt(float t) {
		return o + t * d;
	}

	Ray(Vec3<float> origin, Vec3<float> direction){
		this->o = origin;
		this->d = direction;
	}
};