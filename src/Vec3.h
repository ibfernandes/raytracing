#pragma once
#include <cstddef>
#include <iostream>
#include <math.h>

template<typename T>
class Vec3 {
public:
	union { T x, r;  };
	union { T y, g;  };
	union { T z, b;  };

	inline Vec3<T> operator+ (const Vec3<T> &v1) {
		return Vec3<T>(v1.x + this->x, v1.y + this->y, v1.z + this->z);
	};
	inline Vec3<T> operator+ (const T &v) {
		return Vec3<T>(v + this->x, v + this->y, v + this->z);
	};
	inline Vec3<T> operator- () {
		return Vec3<T>(-this->x, -this->y, -this->z);
	};
	inline Vec3<T> operator- (const Vec3<T> &v1) {
		return Vec3<T>(this->x - v1.x, this->y - v1.y, this->z - v1.z);
	};
	inline Vec3<T> operator* (const Vec3<T> &v1) {
		return Vec3<T>(this->x * v1.x, this->y * v1.y, this->z * v1.z);
	};
	inline Vec3<T> operator* (const T &v) {
		return Vec3<T>(this->x * v, this->y * v, this->z * v);
	};
	inline Vec3<T> operator/ (const Vec3<T> &v1) {
		return Vec3<T>(this->x / v1.x, this->y / v1.y, this->z / v1.z);
	};
	inline Vec3<T> operator/ (const T &v) {
		return Vec3<T>(this->x / v, this->y / v, this->z / v);
	};
	inline bool operator== (const Vec3<T> &v1) {
		return (this->x == v1.x && this->y == v1.y && this->z == v1.z) ? true : false;
	};
	inline Vec3<T> operator+= (const Vec3<T> &v1) {
		this->x += v1.x;
		this->y += v1.y;
		this->z += v1.z;
		return *this;
	};

	inline operator Vec3<int>() {
		return Vec3<int>((int) x, (int)y, (int)z);
	};

	inline Vec3<float> floatmod(float v) {
		return Vec3<int>(fmod(x, v), fmod(y, v), fmod(z, v));
	};

	inline Vec3<int> intmod(int v) {
		return Vec3<int>(x % v, y % v, z % v);
	};

	/*
		Returns the dot product between two vectors. Remember to normalize them!
	*/
	inline float dot(const Vec3<T> v1) {
		return this->x * v1.x + this->y * v1.y + this->z * v1.z;
	}
	
	inline Vec3<T> cross(const Vec3<T> v1) {
		return Vec3<T>(this->y * v1.z - this->z * v1.y, this->z * v1.x - this->x * v1.z, this->x * v1.y - this->y * v1.x );
	}

	inline float length() {
		return sqrt(dot(*this));
	}

	inline float squaredLength() {
		return dot(*this);
	}

	inline Vec3<float> normalize() {
		return Vec3<float>(x,y,z) / this->length();
	}

	inline Vec3<T>(T x) {
		this->x = x;
		this->y = x;
		this->z = x;
	};

	inline Vec3<T>(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	inline Vec3<T>::Vec3() {
	};

	void print() {
		std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
	}
};

template<typename T, typename J>
inline Vec3<T> operator* (const J &v, const Vec3<T> &v1) {
	return Vec3<T>(v * v1.x, v * v1.y, v * v1.z);
};

