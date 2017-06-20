#include "math.h"
#include <string.h>
#include <stdio.h>

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

	vec2 vec2::operator/ (float scale) const {
		vec2 result;
		for (int i = 0; i < 2; i++) {
			result._[i] = _[i] / scale;
		}
		return result;
	}

	// The dot product, if you don't know this, look it up.
	float dot(vec2 const& a, vec2 const& b) {
		float result;
		for (int i = 0; i < 2; i++) {
			result = a._[i] * b._[i];
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
	float coss(vec2 const& a, vec2 const& b) {
		return a.x * b.y - a.y * b.x;
	}

	// The langth, squared...
	float length_squared(vec2 const& a) {
		return a.x * a.x + a.y * a.y;
	}

	// The length of the vector.
	float length(vec2 const& a) {
		return sqrt(length_squared(a));
	}

	// Creates a normalized copy.
	vec2 normalize(vec2 const& a) {
		float l = length(a);
		vec2 result;

		if (l == 0) return result;

		result.x = a.x / l;
		result.y = a.y / l;
		return result;
	}

	// It, spoilers, rotates a vector.
	vec2 rotate(vec2 const& a, float angle) {
		vec2 result;

		float c = cos(angle);
		float s = sin(angle);
		result.x = c * a.x - s * a.y;
		result.y = s * a.x + c * a.y;

		return result;
	}

	// Creates a new matrix.
	mat4::mat4 (float d) {
		for (int i = 0; i < 16; i++) {
			if (i % 5 == 0) {
				_[i] = d;
			} else {
				_[i] = 0;
			}
		}
	}

	float& mat4::operator[] (int i) {
		return this->_[i];
	}

	const float& mat4::operator[] (int i) const{
		return this->_[i];
	}
	
	// Multiplying with another matrix
	mat4 mat4::operator* (mat4 o) const {
		mat4 a;
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				a._[i * 4 + j] += _[i * 4 + k] * o._[k * 4 + j];
			}
		} 
		return a;
	}

	vec4 mat4::operator* (vec4 a) const {
		vec4 out;
		
		for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
			out._[i] += a._[j] * _[i * 4 + j];
		}

		return out;
	}

	vec2 mat4::operator* (vec2 a) const {
		vec4 out = (*this) * vec4(a.x, a.y, 0, 1);
		return vec2(out.x, out.y);
	}

	// Prints the matrix.
	void print_mat(char const* prefix, mat4 const& m) {
		printf("%s:\n", prefix);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				printf("% 04.2f, ", m._[4 * i + j]);
			}
			printf("\b\b \n");
		}
	}

		
	// Adds translation to the matrix, or generates a new one.
	mat4 translation(float x, float y, float z) {
		return translation(mat4(0), x, y, z);
	}

	mat4 translation(mat4 m, float x, float y, float z) {
		m._03 += x;
		m._13 += y;
		m._23 += z;
		return m;
	}

	mat4 translation(vec2 delta_pos) {
		return translation(delta_pos.x, delta_pos.y);
	}

	mat4 translation(mat4 m, vec2 delta_pos) {
		return translation(m, delta_pos.x, delta_pos.y);
	}

	// Adds in rotation in the matrix, around the z-axis 
	//
	// The angle is in radians.
	//
	// (This is made for 2D stuff after all)
	mat4 rotation(float angle) {
		mat4 r(1.0);
		float s = sin(angle);
		float c = cos(angle);
		r._00 =  c;
		r._01 = -s;
		r._10 =  s;
		r._11 =  c;
		return r;
	}

	mat4 rotation(mat4 m, float angle) {
		mat4 r = rotation(angle);
		return r * m;
	}

	// Multiples the scale applied by the matrix.
	mat4 scaling(float scale_x, float scale_y, float scale_z) {
		mat4 s(1);
		s._00 = scale_x;
		s._11 = scale_y;
		s._22 = scale_z;
		return s;
	}

	mat4 scaling(mat4 m, float scale_x, float scale_y, float scale_z) {
		mat4 s = scaling(scale_x, scale_y, scale_z);
		return s * m;
	}

	mat4 gen_transform(transform const& t) {
		return gen_transform(t.position, t.scale, t.rotation);
	}

	// Generates a brand spanking new transform that can be sent into OpenGL.
	mat4 gen_transform(vec2 position, vec2 scale, float angle) {
		mat4 result = scaling(scale.x, scale.y);
		result = rotation(result, angle);
		result = translation(result, position.x, position.y);
		return result;
	}

	mat4 ortho_project(float angle, float aspect_ratio, float zoom) {
		mat4 p(1);
		float a = 1.0f; //zoom.x;
		// OpenGL is upside down.
		float b = -aspect_ratio; //* zoom.y;

		float c = cos(angle);
		float s = sin(angle);

		p._00 =  a * c;
		p._01 = -a * s;
		p._10 =  b * s;
		p._11 =  b * c;

		p._33 = zoom;

		return p;
	}
	
	mat4 invert(mat4 const& m) {
		mat4 inv;
		float det;
		int i;

		inv[0] = m[5]  * m[10] * m[15] - 
			m[5]  * m[11] * m[14] - 
			m[9]  * m[6]  * m[15] + 
			m[9]  * m[7]  * m[14] +
			m[13] * m[6]  * m[11] - 
			m[13] * m[7]  * m[10];

		inv[4] = -m[4]  * m[10] * m[15] + 
			m[4]  * m[11] * m[14] + 
			m[8]  * m[6]  * m[15] - 
			m[8]  * m[7]  * m[14] - 
			m[12] * m[6]  * m[11] + 
			m[12] * m[7]  * m[10];

		inv[8] = m[4]  * m[9] * m[15] - 
			m[4]  * m[11] * m[13] - 
			m[8]  * m[5] * m[15] + 
			m[8]  * m[7] * m[13] + 
			m[12] * m[5] * m[11] - 
			m[12] * m[7] * m[9];

		inv[12] = -m[4]  * m[9] * m[14] + 
			m[4]  * m[10] * m[13] +
			m[8]  * m[5] * m[14] - 
			m[8]  * m[6] * m[13] - 
			m[12] * m[5] * m[10] + 
			m[12] * m[6] * m[9];

		inv[1] = -m[1]  * m[10] * m[15] + 
			m[1]  * m[11] * m[14] + 
			m[9]  * m[2] * m[15] - 
			m[9]  * m[3] * m[14] - 
			m[13] * m[2] * m[11] + 
			m[13] * m[3] * m[10];

		inv[5] = m[0]  * m[10] * m[15] - 
			m[0]  * m[11] * m[14] - 
			m[8]  * m[2] * m[15] + 
			m[8]  * m[3] * m[14] + 
			m[12] * m[2] * m[11] - 
			m[12] * m[3] * m[10];

		inv[9] = -m[0]  * m[9] * m[15] + 
			m[0]  * m[11] * m[13] + 
			m[8]  * m[1] * m[15] - 
			m[8]  * m[3] * m[13] - 
			m[12] * m[1] * m[11] + 
			m[12] * m[3] * m[9];

		inv[13] = m[0]  * m[9] * m[14] - 
			m[0]  * m[10] * m[13] - 
			m[8]  * m[1] * m[14] + 
			m[8]  * m[2] * m[13] + 
			m[12] * m[1] * m[10] - 
			m[12] * m[2] * m[9];

		inv[2] = m[1]  * m[6] * m[15] - 
			m[1]  * m[7] * m[14] - 
			m[5]  * m[2] * m[15] + 
			m[5]  * m[3] * m[14] + 
			m[13] * m[2] * m[7] - 
			m[13] * m[3] * m[6];

		inv[6] = -m[0]  * m[6] * m[15] + 
			m[0]  * m[7] * m[14] + 
			m[4]  * m[2] * m[15] - 
			m[4]  * m[3] * m[14] - 
			m[12] * m[2] * m[7] + 
			m[12] * m[3] * m[6];

		inv[10] = m[0]  * m[5] * m[15] - 
			m[0]  * m[7] * m[13] - 
			m[4]  * m[1] * m[15] + 
			m[4]  * m[3] * m[13] + 
			m[12] * m[1] * m[7] - 
			m[12] * m[3] * m[5];

		inv[14] = -m[0]  * m[5] * m[14] + 
			m[0]  * m[6] * m[13] + 
			m[4]  * m[1] * m[14] - 
			m[4]  * m[2] * m[13] - 
			m[12] * m[1] * m[6] + 
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] + 
			m[1] * m[7] * m[10] + 
			m[5] * m[2] * m[11] - 
			m[5] * m[3] * m[10] - 
			m[9] * m[2] * m[7] + 
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] - 
			m[0] * m[7] * m[10] - 
			m[4] * m[2] * m[11] + 
			m[4] * m[3] * m[10] + 
			m[8] * m[2] * m[7] - 
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] + 
			m[0] * m[7] * m[9] + 
			m[4] * m[1] * m[11] - 
			m[4] * m[3] * m[9] - 
			m[8] * m[1] * m[7] + 
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] - 
			m[0] * m[6] * m[9] - 
			m[4] * m[1] * m[10] + 
			m[4] * m[2] * m[9] + 
			m[8] * m[1] * m[6] - 
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		mat4 inv_out;
		if (det != 0) {
			det = 1.0 / det;

			for (i = 0; i < 16; i++)
				inv_out[i] = inv[i] * det;
		}
		return inv_out;
	}
}
