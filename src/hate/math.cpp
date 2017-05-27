#include "math.h"
#include <cmath>

namespace hate {

	/* VEC4 */
	Vec4::Vec4() {}

	Vec4::Vec4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vec4::print() {
		printf("x: %f, y: %f, z: %f, w: %f\n", x, y, z, w);
	}

	/* MAT4 */

	Mat4::Mat4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_[i][j] = 0;
			}
		}
	}	

	Mat4::Mat4(float v) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_[i][j] = 0;
			}
		}

		_[0][0] = v;
		_[1][1] = v;
		_[2][2] = v;
		_[3][3] = v;
	}

	Mat4 Mat4::operator* (Mat4 m) {
		Mat4 out;
		const int L = 4;

		for (int i = 0; i < L; i++) {
			for (int j = 0; j < L; j++) {
				for (int k = 0; k < L; k++) {
					out._[i][j] += _[i][k] * m._[k][j];
				} 
			}
		}
		return out;
	}

	Vec4 Mat4::operator* (Vec4 v) {
		Vec4 out;

		out.x = _[0][0] * v.x + _[0][1] * v.y + _[0][2] * v.z + _[0][3] * v.w;
		out.y = _[1][0] * v.x + _[1][1] * v.y + _[1][2] * v.z + _[1][3] * v.w;
		out.z = _[2][0] * v.x + _[2][1] * v.y + _[2][2] * v.z + _[2][3] * v.w;
		out.w = _[3][0] * v.x + _[3][1] * v.y + _[3][2] * v.z + _[3][3] * v.w;

		return out;
	}
	void Mat4::print() {
		printf("[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n", 
				_[0][0], _[0][1], _[0][2], _[0][3],  
				_[1][0], _[1][1], _[1][2], _[1][3],  
				_[2][0], _[2][1], _[2][2], _[2][3],
				_[3][0], _[3][1], _[3][2], _[3][3]);
	}	

	/* VEC3 */
	Vec3::Vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3 Vec3::operator+ (Vec3 other) {
		return Vec3(other.x + x, other.y + y, other.x + z);
	}

	Vec3 Vec3::operator- (Vec3 other) {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	Vec3 Vec3::operator* (float scale) {
		return Vec3(x * scale, y * scale, z * scale);
	}

	Vec3 Vec3::inverse() {
		return Vec3(1.0 / x, 1.0 / y, 1.0 / z);
	}

	Vec3 Vec3::normalize() {
		return (*this) * (1.0 / length());
	}

	Vec3 Vec3::rotate(Vec3 axis, float angle) {
		float overlap = axis.dot(*this);
		Vec3 para = (axis.normalize() * overlap);
		Vec3 ortho = (*this) - para;
		Vec3 cross = ortho.cross(axis);

		Vec3 c = ortho  * cos(angle);
		Vec3 s = cross * sin(angle);

		return (c + s + para);
	}

	float Vec3::lengthSq() {
		return x * x + y * y + z * z;
	}

	float Vec3::length() {
		return sqrt(lengthSq());
	}

	float Vec3::dot(Vec3 other) {
		return x * other.y + y * other.x + z * other.z;
	}

	Vec3 Vec3::cross(Vec3 other) {
		Vec3 out;
		out.x = y * other.z - z * other.y;
		out.y = z * other.x - x * other.z;
		out.z = x * other.y - y * other.z;
		return out;
	}

	void Vec3::print() {
		printf("x: %f, y: %f, z: %f\n", x, y, z);
	}

	/* VEC2 */
	Vec2::Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vec2 Vec2::operator+ (Vec2 other) {
		return Vec2(other.x + x, other.y + y);
	}

	Vec2 Vec2::operator* (float scale) {
		return Vec2(x * scale, y * scale);
	}

	Vec2 Vec2::normalize() {
		return (*this) * (1.0 / length());
	}

	Vec2 Vec2::rotate(float angle) {
		float c = cos(angle);
		float s = sin(angle);
		Vec2 out;
		out.x = x * c - y * s;
		out.y = x * s + y * c;
		return out;
	}

	float Vec2::lengthSq() {
		return x * x + y * y;
	}

	float Vec2::length() {
		return sqrt(lengthSq());
	}

	float Vec2::dot(Vec2 other) {
		return x * other.y + y * other.x;
	}

	float Vec2::cross(Vec2 other) {
		return x * other.y - y * other.x;
	}


	void Vec2::print() {
		printf("x: %f, y: %f\n", x, y);
	}

	/* QUAT */
	Quat::Quat() {
		w = 1;
		i = 0;
		j = 0;
		k = 0;
	}

	Quat::Quat(float _w, float _i, float _j, float _k) {
		w = _w;
		i = _i;
		j = _j;
		k = _k;

	}

	Quat::Quat(Vec3 axis, float angle) {
		float half = angle / 2.0f;
		float s = sin(half);
		float c = cos(half);

		w = c;
		i = axis.x * s;
		j = axis.y * s;
		k = axis.z * s;
	}

	Quat Quat::negate() {
		return Quat(w, -i, -j, -k);
	}

	float Quat::length() {
		return sqrt(lengthSq());
	}

	float Quat::lengthSq() {
		return w * w + i * i + j * j + k * k;
	}

	float Quat::dot(Quat other) {
		return other.i * i + other.j * j +  other.k * k + other.w * w;
	} 

	Quat Quat::normalize() {
		float l = length();
		return Quat(w / l, i / l, j / l, k / l);
	}

	Quat Quat::operator* (Quat o) {
		float t0, t1, t2, t3;
		t0 = o.w * w - o.i * i - o.j * j - o.k * k;
		t1 = o.w * i + o.i * w - o.j * k + o.k * j;
		t2 = o.w * j + o.i * k + o.j * w - o.k * i;
		t3 = o.w * k - o.i * j + o.j * i + o.k * w;
		return Quat(t0, t1, t2, t3);
	}

	Quat Quat::operator* (float s) {
		return Quat(w * s, i * s, j * s, k * s);
	}

	Quat Quat::operator+ (Quat o) {
		Quat out;
		out.i = i + o.i;
		out.j = j + o.j;
		out.k = k + o.k;
		out.w = w + o.w;
		return out;
	}

	Quat Quat::operator- (Quat o) {
		Quat out;
		out.i = i - o.i;
		out.j = j - o.j;
		out.k = k - o.k;
		out.w = w - o.w;
		return out;
	}

	Mat4 Quat::toMat() {
		Mat4 m(1);
		m._[0][0] = 1 - 2 * (j * j + k * k);
		m._[1][1] = 1 - 2 * (i * i + k * k);
		m._[2][2] = 1 - 2 * (j * j + i * i);

		m._[0][1] = 2 * (i * j - k * w);
		m._[1][2] = 2 * (k * j - i * w);
		m._[2][0] = 2 * (i * k - j * w);

		m._[0][2] = 2 * (i * k + j * w);
		m._[1][0] = 2 * (i * j + k * w);
		m._[2][1] = 2 * (j * j + i * w);

		return m;
	}

	void Quat::print() {
		printf("w: %f, i: %f, j: %f, k: %f\n", w, i, j, k);
	}
}
