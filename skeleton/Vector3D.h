#pragma once

#include <cmath>

template <typename T = float>
class Vector3D {
public:
	T x;
	T y;
	T z;

	Vector3D() :
		x(0), y(0), z(0) {}

	Vector3D(T xComponent, T yComponent, T zComponent) :
		x(xComponent), y(yComponent), z(zComponent) {}

	float GetMagnitude() const {
		return sqrt(x ^ 2 + y ^ 2 + z ^ 2);
	}

	Vector3D<T> GetNormalized() const {
		float magnitude = sqrt(x ^ 2 + y ^ 2 + z ^ 2);
		return Vector3D<T>(x / magnitude, y / magnitude, z / magnitude);
	}

	void Normalize() {
		float magnitude = sqrt(x ^ 2 + y ^ 2 + z ^ 2);
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	static Vector3D<T> Dot(Vector3D<T> v1, Vector3D<T> v2) {

	}

};