#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include <assert.h>

void assertOperators() {
	Vec3<float> v1(1, 2, 3);
	Vec3<float> v2(4, 5, -6);
	Vec3<float> result;

	result = v1 + v2;
	result.print();
	assert(result == Vec3<float>(5, 7, -3));

	result = v1 - v2;
	result.print();
	assert(result == Vec3<float>(-3, -3, 9));

	result = v1 * v2;
	result.print();
	assert(result == Vec3<float>(4, 10, -18));

	result = v1 * 2;
	result.print();
	assert(result == Vec3<float>(2, 4, 6));

	result = 2 * v1;
	result.print();
	assert(result == Vec3<float>(2, 4, 6));

	result = v1/v2;
	result.print();
	assert(result == Vec3<float>(1.0f/4.0f, 2.0f/5.0f, 3.0/-6.0f));

	v1 = Vec3<float>(0,1,0);
	v2 = Vec3<float>(1, 0, 0);

	assert(v1.dot(v2) == 0);
	assert(v1.cross(v2) == Vec3<float>(0,0,-1));
}

Vec3<float> blend(Vec3<float> v1, Vec3<float> v2, float t) {
	return (1.0f - t) * v1 + t * v2;
}

Vec3<int> calculateColor(Ray r) {
	Vec3<float> dir = r.direction.normalize();
	float t = 0.5f * (dir.y + 1.0);
	return 255.0f * blend(Vec3<float>(1.0f, 1.0f, 1.0f), Vec3<float>(0.5f, 0.7f, 1.0f), t);
}

int main() {
	assertOperators();
	const int windowWidth = 800, windowHeight = 600;
	Vec3<float> lowerLeft(-2, -1, -1);
	Vec3<float> horizontal(4, 0, 0);
	Vec3<float> vertical(0, 2, 0);
	Vec3<float> origin(0, 0, 0);

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