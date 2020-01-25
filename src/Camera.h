#pragma once
#include "Math.h"
#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
	Vec3<float> u, r, d;
	Vec3<float> lowerLeft;
	Vec3<float> horizontal;
	Vec3<float> vertical;
	Vec3<float> origin;
	float lensRadius;

	/*
		vfov in degrees;
	*/
	Camera(Vec3<float> lookFrom, Vec3<float> lookAt, Vec3<float> up, float vfov, float aspectRatio, float aperture, float focusDistance) {
		lensRadius = aperture / 2.0f;
		float theta = radians(vfov);
		float halfHeight = tan(theta / 2.0f);
		float halfWidth = aspectRatio * halfHeight;
		
		origin = lookFrom;
		d = (lookFrom - lookAt).normalize();
		u = up.cross(d).normalize();
		r = d.cross(u);

		lowerLeft = origin - focusDistance * halfWidth * u - focusDistance * halfHeight * r - focusDistance * d;
		horizontal = 2.0f * focusDistance * halfWidth * u;
		vertical = 2.0f * focusDistance * halfHeight * r;
	}
	
	Ray getRayPassingThrough(float u, float v) {
		return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
	}
	
	/*Ray getRayPassingThrough(float s, float t) {
		Vec3<float> rd = lensRadius * randomInUnitDisk();
		Vec3<float> offset = u * rd.x + r * rd.y;
		return Ray(origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset);
	}*/
};

