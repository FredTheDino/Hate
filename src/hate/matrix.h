// The math class, the actual core of the engine.
//
// This is ment to be held simple, hence there is
// a limited set of functions.
#pragma once
#include <math.h>

namespace hate {
	// I almost only need this for color...
	// Might rework this into a seperate color
	// data structure if that's all I want.
	class Vec4 {
		public:
			union {
				struct {
					float
						x,
						y,
						z,
						w;
				};
				struct {
					float
						r,
						g,
						b,
						a;
				};
				float _[4];
			};

			Vec4(float x = 0, float y = 0, float z = 0, float w = 0) {
				r = x;
				g = y;
				b = z;
				a = w;
			}
	};

	// If you need 2 floats, or a direction
	// in 2D space, this is you jam.
	class Vec2 {
		public:
		// This is legit, a good feature in C++,
		// the first one I've found.
		union {
			struct {
				float x, y;
			};
			struct {
				float r, g;
			};
			float _[2];
		};

		// Can you guess, what this does?
		Vec2(float x = 0, float y = 0);

		// Adds the other vector to this vector.
		Vec2 operator+ (Vec2 other) const; 

		// Subtracts the other vector to this vector.
		Vec2 operator- (Vec2 other) const; 

		// Scales the vector by a scaler.
		Vec2 operator* (float scale) const; 
		
		// Scales the vector by the inverse of a scaler.
		Vec2 operator/ (float scale) const; 
	};

	// The dot product, if you don't know this, look it up.
	float dot(Vec2 const& a, Vec2 const& b); 

	// This isn't really a cross product,
	// but it is the dot product of the two
	// vectors after one has been rotated 90 
	// degrees.
	//
	// This can be used for telling if the 
	// points in a polygon are named in counter
	// clockwise or clockwise order.
	//
	// But yeah, it's wierd.
	float cross(Vec2 const& a, Vec2 const& b); 

	// The langth, squared...
	float length_squared(Vec2 const& a); 

	// The length of the vector.
	float length(Vec2 const& a); 

	// Creates a normalized copy.
	Vec2 normalize(Vec2 const& a); 

	// Rotates the vector around the origin by
	// the angle "angle". Note that this uses
	// radians.
	Vec2 rotate(Vec2 const& a, float angle);

	// A row major matrix implementation that
	// cuts out all the fluff.
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
				float _[16];
			};
			
			// Inintalizes a new matrix.
			Mat4 (float d = 0);

			float& operator[] (int i);
			const float& operator[] (int i) const;
			
			// Multiplies the two matricies.
			Mat4 operator* (Mat4 o) const; 

			// Transforms a vector.
			Vec4 operator* (Vec4 a) const;

			Vec2 operator* (Vec2 a) const;
	};

	// A transform, because it's usefull.
	struct Transform {
		Vec2 position;
		Vec2 scale = Vec2(1, 1);
		float rotation;
	};

	// #Functional #Precompiled #Rad
	inline int num_elements(Mat4 m) { return 16; }

	//
	// Some simple to use matrix manipulations functions.
	//

	// Prints the matrix.
	extern void print_mat(char const* prefix, Mat4 const& m);

	// Adds translation to the matrix, or generates a new one.
	extern Mat4 translation(float x, float y = 0, float z = 0);
	extern Mat4 translation(Mat4 m, float x, float y = 0, float z = 0);
	extern Mat4 translation(Vec2 delta_pos);
	extern Mat4 translation(Mat4 m, Vec2 delta_pos);

	// Adds in rotation in the matrix, around the z-axis 
	//
	// The angle is in radians.
	//
	// (This is made for 2D stuff after all)
	extern Mat4 rotation(float angle);
	extern Mat4 rotation(Mat4 m, float angle);

	// Multiples the scale applied by the matrix.
	extern Mat4 scaling(float scale_x, float scale_y = 1, float scale_z = 1);
	extern Mat4 scaling(Mat4 m, float scale_x, float scale_y = 1, float scale_z = 1);

	// Generates a brand spanking new transform that can be sent into OpenGL.
	extern Mat4 gen_transform(Transform const& t);
	extern Mat4 gen_transform(Vec2 position, Vec2 scale, float angle);

	// Generaties an orthographic projection matrix.
	extern Mat4 ortho_project(float angle, float aspect_ratio, float zoom = 1.0f);

	// Inverts the matrix (AKA generates a matrix which reverses the effects of the old one)
	extern Mat4 invert(Mat4 const& m);
}
