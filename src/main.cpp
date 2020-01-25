#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Model.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Math.h"
#include "DiffuseMaterial.h"
#include "DielectricMaterial.h"
#include "MetalMaterial.h"
#include <assert.h>
#include <Vector>
#include <limits>
#include <cstddef>

std::vector<Model*> models;

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

Vec3<float> calculateColor(Ray r, int depth) {
	Hit hit;
	float albedo = 0.5;
	if(checkHits(r, 0.001, std::numeric_limits<float>::max(), hit)){
		Ray scattered;
		Vec3<float> attenuation;

		if (depth < 50 && hit.material->scatter(r, hit, attenuation, scattered))
			return attenuation * calculateColor(scattered, depth + 1);
		else
			return Vec3<float>(0, 0, 0);
	}

	Vec3<float> dir = r.direction.normalize();
	float t = 0.5f * (dir.y + 1.0);
	return blend(Vec3<float>(1.0f, 1.0f, 1.0f), Vec3<float>(0.5f, 0.7f, 1.0f), t);
}

int main() {
	const int windowWidth = 200, windowHeight = 100, totalPixels = windowWidth * windowHeight;
	const int spp = 100;
	Vec3<float> lookFrom(0, 1, 1.5f);
	Vec3<float> lookAt(0, 0, -1);
	Camera cam(lookFrom, lookAt, Vec3<float>(0, 1, 0), 90.0f, float(windowWidth) / float(windowHeight), 2.0f, (lookFrom - lookAt).length());
	
	models.push_back(&Sphere(Vec3<float>(0, 0, -1.0f), 0.5f, new DiffuseMaterial(Vec3<float>(1.0, 0.1, 0.1))));
	models.push_back(&Sphere(Vec3<float>(1.0f, 0, -1.0f), 0.5f, new DielectricMaterial(1.5f)));
	//models.push_back(&Sphere(Vec3<float>(0, -100.5f, -1), 100.0f, new MetalMaterial(Vec3<float>(0.8, 0.8, 0.8))));
	models.push_back(&Sphere(Vec3<float>(0, -100.5f, -1), 100.0f, new DiffuseMaterial(Vec3<float>(0.5, 0.5, 0.5))));

	for (int x = 0; x < 5; x++) {
		for (int z = 0; z < 5; z++) {
			Vec3<float> center((random()*2 -1) * 5, 0.2, -random() * 5);
			float materialChance = random();

			if (materialChance < 0.8)
				models.push_back(&Sphere(center, random() * 0.5f, new DiffuseMaterial(Vec3<float>(random()*random(), random()*random(), random()*random()))));
			else if (materialChance < 0.95)
				models.push_back(&Sphere(center, random() * 0.5f, new MetalMaterial(Vec3<float>(0.5 * (1 + random()), 0.5 * (1 + random()), 0.5 * (1 + random())))));
			else
				models.push_back(&Sphere(center, random() * 0.5f, new DielectricMaterial(1.5f)));
		}
	}

	Vec3<float> vec;

	std::ofstream file;
	file.open("output.ppm");
	file << "P3\n" << windowWidth << " " << windowHeight << "\n255\n";
	std::cout << "Processing..." << std::endl;

	//writes from left to right, from top to bottom.
	for (int y = windowHeight-1; y >= 0; y--) {
		for (int x = 0; x < windowWidth; x++) {
			int pos = x + (windowHeight - y) * windowWidth;

			if(pos == int(totalPixels * 0.25f))
				std::cout << "25% done..." << std::endl;
			else if (pos == int(totalPixels * 0.50f))
				std::cout << "50% done..." << std::endl;
			else if (pos == int(totalPixels * 0.75f))
				std::cout << "75% done..." << std::endl;

			Vec3<float> color(0,0,0);
			for (int s = 0; s < spp; s++) {
				float u = float(x + random()) / windowWidth;
				float v = float(y + random()) / windowHeight;
				Ray r = cam.getRayPassingThrough(u, v);
				color += calculateColor(r, 0);
			}
			color = color / spp;
			color = 255.0f * Vec3<float>(sqrt(color.x), sqrt(color.y), sqrt(color.z));

			file << (int)color.x << " " << (int)color.y << " " << (int)color.z << "\n";
		}
	}

	file.close();
	std::cout << "File output.ppm written with successs" << std::endl;
	return 0;
}