#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Model.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include <assert.h>
#include <Vector>
#include <limits>

std::vector<Model*> models;
Vec3<float> seed(0, 0, 0);

float fraction(float f) {
	int v = f;
	return f - float(v);
}

/*
	Returns a random number between [0, 1)
*/
float random() {
	seed = seed + Vec3<float>(1, 1, 1);
	return fraction(sin(seed.dot(Vec3<float>(12.9898, 4.1414, 0))) * 43758.5453) * 0.5f + 0.5f;
}

Vec3<float> blend(Vec3<float> v1, Vec3<float> v2, float t) {
	return (1.0f - t) * v1 + t * v2;
}

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

	//Simple test to check if in fact my random generator is uniformly distributed.
	float acc = 0;
	int histogram[10]{0,0,0,0,0,0,0,0,0,0};
	for (int i = 0; i < 100000; i++) {
		float r = random();
		histogram[(int)(r*10)]++;
		acc += r;
	}
	std::cout << acc / 100000.0f;
	for (int i = 0; i < 10; i++) {
		std::cout << histogram[i] << std::endl;
	}

	const int windowWidth = 200, windowHeight = 100;
	const int spp = 100;
	Camera cam;

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

			Vec3<int> color(0,0,0);
			for (int s = 0; s < spp; s++) {
				float u = float(x + random()) / windowWidth;
				float v = float(y + random()) / windowHeight;
				Ray r = cam.getRayPassingThrough(u, v);
				color += calculateColor(r);
			}
			color = color / spp;

			file << color.x << " " << color.y << " " << color.z << "\n";
		}
	}

	file.close();
	std::cout << "File output.ppm written with successs";
	return 0;
}