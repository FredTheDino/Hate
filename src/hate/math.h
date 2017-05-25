#pragma once
#include <cmath>

/**
 * A collection of usefull math constructs.
 */
namespace hate {
	class Vec2;
	class Vec3;
	class Vec4;

	class Vec4 {
	public:
		float x;
		float y;
		float z;
		float w;

		Vec4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
	};

	class Vec3 {
	public:
		float x;
		float y;
		float z;

		Vec3(float x = 0, float y = 0, float z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vec3 operator+ (Vec3 other) {
			return Vec3(other.x + x, other.y + y, other.x + z);
		}

		Vec3 operator- (Vec3 other) {
			return Vec3(x - other.x, y - other.y, z - other.z);
		}

		Vec3 operator* (float scale) {
			return Vec3(x * scale, y * scale, z * scale);
		}

		Vec3 inverse() {
			return Vec3(1.0 / x, 1.0 / y, 1.0 / z);
		}

		Vec3 normalize() {
			return (*this) * (1.0 / length());
		}

		Vec3 rotate(Vec3 axis, float angle) {
			float overlap = axis.dot(*this);
			Vec3 para = (axis.normalize() * overlap);
			Vec3 ortho = (*this) - para;
			Vec3 cross = ortho.cross(axis);

			Vec3 c = ortho  * cos(angle);
			Vec3 s = cross * sin(angle);

			return (c + s + para);
		}

		float lengthSq() {
			return x * x + y * y + z * z;
		}

		float length() {
			return sqrt(lengthSq());
		}
		
		float dot(Vec3 other) {
			return x * other.y + y * other.x + z * other.z;
		}

		Vec3 cross(Vec3 other) {
			Vec3 out;
			out.x = y * other.z - z * other.y;
			out.y = z * other.x - x * other.z;
			out.z = x * other.y - y * other.z;
			return out;
		}

		/*
		operator Vec2() const {
			return Vec2(x, y);
		}
		*/

		operator Vec4() const {
			return Vec4(x, y, 0, 1);
		}
	};

	class Vec2 {
	public:
		float x;
		float y;

		Vec2(float x = 0, float y = 0) {
			this->x = x;
			this->y = y;
		}

		Vec2 operator+ (Vec2 other) {
			return Vec2(other.x + x, other.y + y);
		}

		Vec2 operator* (float scale) {
			return Vec2(x * scale, y * scale);
		}

		Vec2 normalize() {
			return (*this) * (1.0 / length());
		}

		Vec2 rotate(float angle) {
			float c = cos(angle);
			float s = sin(angle);
			Vec2 out;
			out.x = x * c - y * s;
			out.y = x * s + y * c;
			return out;
		}

		float lengthSq() {
			return x * x + y * y;
		}

		float length() {
			return sqrt(lengthSq());
		}
		
		float dot(Vec2 other) {
			return x * other.y + y * other.x;
		}

		float cross(Vec2 other) {
			return x * other.y - y * other.x;
		}

		operator Vec3() const {
			return Vec3(x, y, 0);
		}

		operator Vec4() const {
			return Vec4(x, y, 0, 1);
		}
	};
}
