// The math class, the actual core of the engine.
//
// This is ment to be held simple, hence there is
// a limited set of functions.
#pragma once
#include <cmath>

namespace hate {
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
			
			mat4 (float d = 0);

			mat4 operator* (mat4 o); 
	};
}
