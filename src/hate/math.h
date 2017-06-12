// The math class, the actual core of the engine.
//
// This is ment to be held simple, hence there is
// a limited set of functions.
#pragma once
#include <cmath>

namespace hate {
	// I almost only need this for color...
	// Might rework this into a seperate color
	// data structure if that's all I want.
	class vec4 {
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

			vec4(float x = 0, float y = 0, float z = 0, float w = 0) {
				r = x;
				g = y;
				b = z;
				a = w;
			}
	};

	// If you need 2 floats, or a direction
	// in 2D space, this is you jam.
	class vec2 {
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
		vec2(float x = 0, float y = 0);

		// Adds the other vector to this vector.
		vec2 operator+ (vec2 other) const; 

		// Subtracts the other vector to this vector.
		vec2 operator- (vec2 other) const; 

		// Scales the vector by a scaler.
		vec2 operator* (float scale) const; 

		// The dot product, if you don't know this, look it up.
		float dot(vec2 other) const; 

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
		float cross(vec2 other) const; 

		// The langth, squared...
		float length_squared() const; 

		// The length of the vector.
		float length() const; 

		// Creates a normalized copy.
		vec2 normalize() const; 
	};

	// A row major matrix implementation that
	// cuts out all the fluff.
	class mat4 {
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
			mat4 (float d = 0);
			
			// Multiplies the two matricies.
			mat4 operator* (mat4 o); 
	};

	// A transform, because it's usefull.
	struct transform {
		vec2 position;
		vec2 scale;
		float rotation;
	};

	// #Functional #Precompiled #Rad
	inline int num_elements(mat4 m) { return 16; }

	//
	// Some simple to use matrix manipulations functions.
	//

	// Adds translation to the matrix, or generates a new one.
	extern mat4 translation(float x, float y = 0, float z = 0);
	extern mat4 translation(mat4 m, float x, float y = 0, float z = 0);

	// Adds in rotation in the matrix, around the z-axis 
	//
	// The angle is in radians.
	//
	// (This is made for 2D stuff after all)
	extern mat4 rotation(float angle);
	extern mat4 rotation(mat4 m, float angle);

	// Multiples the scale applied by the matrix.
	extern mat4 scaling(float scale_x, float scale_y = 1, float scale_z = 1);
	extern mat4 scaling(mat4 m, float scale_x, float scale_y = 1, float scale_z = 1);

	// Generates a brand spanking new transform that can be sent into OpenGL.
	extern mat4 gen_transform(transform const& t);
	extern mat4 gen_transform(vec2 position, vec2 scale, float angle);

	// Generaties an orthographic projection matrix.
	extern mat4 ortho_project(float angle, float aspect_ratio, float zoom = 1.0f);
}
