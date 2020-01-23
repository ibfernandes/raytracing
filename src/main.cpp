#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Model.h"
#include "Sphere.h"
#include "Ray.h"
#include <assert.h>
#include <Vector>
#include <limits>

Vec3<float> blend(Vec3<float> v1, Vec3<float> v2, float t) {
	return (1.0f - t) * v1 + t * v2;
}

std::vector<Model*> models;

bool checkHits(Ray &r, float tMin, float tMax, Hit &hit) {
	
	Hit tempHit;
	bool hitAnything = false;
	float closestHit = tMax;
	
	for (Model *m : models) {
		if (m->hit(r, tMin, closestHit, tempHit)) {
			hitAnything = true;
			closestHit = tempHit.t;
			hit = tempHit;
		}
	}

	return hitAnything;
}

Vec3<int> calculateColor(Ray r) {
	Hit hit;
	if(checkHits(r, 0, std::numeric_limits<float>::max(), hit)){
		return 255.0f * ( (hit.normal + 1) * 0.5f );
	}

	Vec3<float> dir = r.direction.normalize();
	float t = 0.5f * (dir.y + 1.0);
	return 255.0f * blend(Vec3<float>(1.0f, 1.0f, 1.0f), Vec3<float>(0.5f, 0.7f, 1.0f), t);
}

int main() {
	const int windowWidth = 200, windowHeight = 100;
	Vec3<float> lowerLeft(-2, -1, -1);
	Vec3<float> horizontal(4, 0, 0);
	Vec3<float> vertical(0, 2, 0);
	Vec3<float> origin(0, 0, 0);

	Sphere s1(Vec3<float>(0, 0, -1.0f), 0.5f);
	Sphere s2(Vec3<float>(0, -100.5f, -1), 100.0f);
	models.push_back(&s1);
	models.push_back(&s2);

	std::ofstream file;
	file.open("output.ppm");
	file << "P3\n" << windowWidth << " " << windowHeight << "\n255\n";

	//writes from left to right, from top to bottom.
	for (int y = windowHeight-1; y >= 0; y--) {
		for (int x = 0; x < windowWidth; x++) {
			float px = float(x) / windowWidth;
			float py = float(y) / windowHeight;
			Ray r(origin, lowerLeft + px*horizontal + py*vertical);
			Vec3<int> color = calculateColor(r);

			file << color.x << " " << color.y<< " " << color.z << "\n";
		}
	}

	file.close();
	std::cout << "File output.ppm written with successs";
	return 0;
}