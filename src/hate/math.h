#pragma once
#include <cmath>
#include <stdio.h>

/**
 * A collection of usefull math constructs.
 *
 * This includes, Vec4, Vec3, Vec2, Mat4, Quat.
 */
namespace hate {
	class Vec2;
	class Vec3;
	class Vec4;
	class Quat;

	class Vec4 {
		public:
			float x = 0;
			float y = 0;
			float z = 0;
			float w = 0;

			Vec4() {}

			Vec4(float x, float y, float z, float w) {
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}

			void print() {
				printf("x: %f, y: %f, z: %f, w: %f\n", x, y, z, w);
			}
	};

	class Mat4 {
		public:
			union {
				struct {
					float
						_00,
						_01,
						_02,
						_03,
						_10,
						_11,
						_12,
						_13,
						_20,
						_21,
						_22,
						_23,
						_30,
						_31,
						_32,
						_33;
				};
				float _[4][4];
			};

			Mat4() {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						_[i][j] = 0;
					}
				}
				/*
				_[0][0] = 1;
				_[1][1] = 1;
				_[2][2] = 1;
				_[3][3] = 1;
				*/
			}	

			Mat4(float v) {
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

			Mat4 operator* (Mat4 m) {
				Mat4 out;
				const int L = 4;

				for (int i = 0; i < L; i++) {
					for (int j = 0; j < L; j++) {
						for (int k = 0; k < L; k++) {
							out._[i][j] += _[i][k] * m._[k][j];
							printf("%d%d x %d%d + ", i, k, k, j);
						} 
						printf("\n");
					}
				}
				return out;
			}

			Vec4 operator* (Vec4 v) {
				Vec4 out;

				out.x = _[0][0] * v.x + _[0][1] * v.y + _[0][2] * v.z + _[0][3] * v.w;
				out.y = _[1][0] * v.x + _[1][1] * v.y + _[1][2] * v.z + _[1][3] * v.w;
				out.z = _[2][0] * v.x + _[2][1] * v.y + _[2][2] * v.z + _[2][3] * v.w;
				out.w = _[3][0] * v.x + _[3][1] * v.y + _[3][2] * v.z + _[3][3] * v.w;

				return out;
			}

			void print() {
				printf("[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n", 
						_[0][0], _[1][0], _[2][0], _[3][0],  
						_[0][1], _[1][1], _[2][1], _[3][1],  
						_[0][2], _[1][2], _[2][2], _[3][2],
						_[0][3], _[1][3], _[2][3], _[3][3]);
			}	
	};


	class Vec3 {
		public:
			union {
				struct {
					float x, y, z;
				};
				struct {
					float r, g, b;
				};
				float _[3];
			};

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

			void print() {
				printf("x: %f, y: %f, z: %f\n", x, y, z);
			}
	};

	class Vec2 {
		public:
			union {
				struct {
					float x, y;
				};
				struct {
					float r, g;
				};
				float _[2];
			};

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

			void print() {
				printf("x: %f, y: %f\n", x, y);
			}
	};

	class Quat {
		public:
			union {
				struct {
					float w, i, j, k;
				};
				float _[4];
			};

			Quat(float _w, float _i, float _j, float _k) {
				w = _w;
				i = _i;
				j = _j;
				k = _k;

			}

			Quat(Vec3 axis, float angle) {
				float half = angle / 2.0f;
				float s = sin(half);
				float c = cos(half);

				w = c;
				i = axis.x * s;
				j = axis.y * s;
				k = axis.y * s;
			}

			Quat negate() {
				return Quat(w, -i, -j, -k);
			}

			Quat operator* (Quat o) {
				float t0, t1, t2, t3;
				t0 = o.w * w - o.i * i - o.j * j - o.k * k;
				t1 = o.w * i + o.i * w - o.j * k + o.k * j;
				t2 = o.w * j + o.i * k + o.j * w - o.k * i;
				t3 = o.w * k - o.i * j + o.j * i + o.k * w;
				return Quat(w, i, j, k);
			}

			Mat4 toMat() {
				Mat4 m;
				m._[0][0] = 1 - 2 * (j * j + k * k);
				m._[0][1] = 1 - 2 * (i * i + k * k);
				m._[0][2] = 1 - 2 * (j * j + i * i);

				m._[0][0] = 2 * (i * j - k * w);
				m._[0][1] = 2 * (k * j - i * w);
				m._[0][2] = 2 * (i * k - j * w);

				m._[0][0] = 2 * (i * k + j * w);
				m._[0][1] = 2 * (i * j + k * w);
				m._[0][2] = 2 * (j * j + i * w);

				return m;
			}

			void print() {
				printf("w: %f, i: %f, j: %f, k: %f\n", w, i, j, k);
			}
	};
}
