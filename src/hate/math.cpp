#include "math.h"

namespace hate {
	
	vec2::vec2(float x, float y) {
		_[0] = x;	
		_[1] = y;	
	}

	// Adds the other vector to this vector.
	vec2 vec2::operator+ (vec2 other) const {
		vec2 result;
		for (int i = 0; i < 2; i++) {
			result._[i] = other._[i] + _[i];
		}
		return result;
	}

	// Subtracts the other vector to this vector.
	vec2 vec2::operator- (vec2 other) const {
		vec2 result;
		for (int i = 0; i < 2; i++) {
			result._[i] = other._[i] - _[i];
		}
		return result;
	}

	// Scales the vector by a scaler.
	vec2 vec2::operator* (float scale) const {
		vec2 result;
		for (int i = 0; i < 2; i++) {
			result._[i] = _[i] * scale;
		}
		return result;
	}

	// The dot product, if you don't know this, look it up.
	float vec2::dot(vec2 other) const {
		float result;
		for (int i = 0; i < 2; i++) {
			result = other._[i] * _[i];
		}
		return result;
	}

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
	float vec2::cross(vec2 other) const {
		return x * other.y - y * other.x;
	}

	// The langth, squared...
	float vec2::length_squared() const {
		return x * x + y * y;
	}

	// The length of the vector.
	float vec2::length() const {
		return sqrt(length_squared());
	}

	// Creates a normalized copy.
	vec2 vec2::normalize() const {
		float l = length();
		vec2 result;
		result.x = x / l;
		result.y = y / l;
		return result;
	}

	// Creates a new matrix.
	mat4::mat4 (float d) {
		for (int i = 0; i < 16; i++) {
			if (i % 5 == 0)
				_[i] = d;
			else
				_[i] = 0;
		}
	}
	
	// Multiplying with another matrix
	mat4 mat4::operator* (mat4 o) {
		mat4 a;
		for (int i = 0; i < 16; i++) for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 4; k++) {
				a._[i * 4 + j] += _[i * 4 + k] * o._[k * 4 + j];
			}
		} 
		return a;
	}
}
