#pragma once

#include <cmath>
#include <iostream>

template <typename T = float>
class Vector3D {
public:
	T x;
	T y;
	T z;

	Vector3D() noexcept  :
		x(0), y(0), z(0) {}

	Vector3D(const Vector3D<T>& v) noexcept :
		x(v.x), y(v.y), z(v.z) {
	}

	Vector3D(const Vector3D<T>&& v) noexcept :
		x(v.x), y(v.y), z(v.z) {
	}
	Vector3D(T xComponent, T yComponent, T zComponent) noexcept :
		x(xComponent), y(yComponent), z(zComponent) {}

	float GetMagnitude() const {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vector3D<T> GetNormalized() const {
		float magnitude = GetMagnitude();
		return Vector3D<T>(x / magnitude, y / magnitude, z / magnitude);
	}

	void Normalize() {
		float magnitude = GetMagnitude();
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	static T Dot(Vector3D<T> v1, Vector3D<T> v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static Vector3D<T> Cross(Vector3D<T> v1, Vector3D<T> v2) {
		return Vector3D<T>(v1.y * v2.z - v1.z * v2.y,
						   v1.z * v2.x - v1.x * v2.z,
						   v1.x * v2.y - v1.y * v2.x);
	}

	void Scale(T scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	static float Angle(Vector3D<T> v1, Vector3D<T> v2) {
		return acos(Dot(v1.GetNormalized(), v2.GetNormalized())) * 180 / 3.1415926536;
	}

	Vector3D<T>& operator=(const Vector3D<T>& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}

	Vector3D<T> operator+(const Vector3D<T>& other) {
		return Vector3D<T>(x + other.x, y + other.y, z + other.z);
	}

	Vector3D<T> operator-(const Vector3D<T>& other) {
		return Vector3D<T>(x - other.x, y - other.y, z - other.z);
	}

	Vector3D<T> operator*(const T& scalar) {
		Scale(scalar);
		return *this;
	}

	Vector3D<T> operator*(const Vector3D<T>& other) {
		return Cross(*this, other);
	}

	Vector3D<T> operator/(const T& other) {
		return Vector3D<T>(x / other, y / other, z / other);
	}

	bool operator==(const Vector3D<T>& other) {
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const Vector3D<T>& other) {
		return !(x == other.x && y == other.y && z == other.z);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3D<T>& v) {
		os << "[ " << v.x << " | " << v.y << " | " << v.z << " ]";
		return os;
	}

};