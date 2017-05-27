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

			Vec4();

			Vec4(float x, float y, float z, float w);

			void print();
	};

	class Mat4 {
		public:
			union {
				struct {
					float
						_00, _01, _02, _03,
						_10, _11, _12, _13,
						_20, _21, _22, _23,
						_30, _31, _32, _33;
				};
				float _[4][4];
			};

			// NOTE: This zeroes everything.
			Mat4();

			Mat4(float v);

			Mat4 operator* (Mat4 m);

			Vec4 operator* (Vec4 v);

			void print();
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

			Vec3(float x = 0, float y = 0, float z = 0); 

			Vec3 operator+ (Vec3 other);

			Vec3 operator- (Vec3 other);

			Vec3 operator* (float scale);

			Vec3 inverse();

			Vec3 normalize();

			Vec3 rotate(Vec3 axis, float angle);

			float lengthSq();

			float length();

			float dot(Vec3 other);

			Vec3 cross(Vec3 other);

			operator Vec4() const {
				return Vec4(x, y, 0, 1);
			}

			void print();
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

			Vec2(float x = 0, float y = 0);

			Vec2 operator+ (Vec2 other);

			Vec2 operator* (float scale);

			Vec2 normalize();

			Vec2 rotate(float angle);

			float lengthSq();

			float length();

			float dot(Vec2 other);

			float cross(Vec2 other);

			operator Vec3() const {
				return Vec3(x, y, 0);
			}

			operator Vec4() const {
				return Vec4(x, y, 0, 1);
			}

			void print();
	};

	class Quat {
		public:
			union {
				struct {
					float w, i, j, k;
				};
				float _[4];
			};

			Quat();

			Quat(float _w, float _i, float _j, float _k);

			Quat(Vec3 axis, float angle);

			Quat negate();
			
			float dot(Quat other);

			float length();

			float lengthSq();

			Quat normalize();

			Quat operator* (Quat o);

			Quat operator* (float s);

			Quat operator+ (Quat o);
			
			Quat operator- (Quat o);

			Mat4 toMat();

			void print();
	};
}
