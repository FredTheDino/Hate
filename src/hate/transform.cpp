#include "transform.h"

namespace hate {
	Transform::Transform() {}

	Transform::Transform(Vec3 _position, Vec3 _scale, Quat _orientation) {
		p = _position;
		s = _scale;
		o = _orientation;
	}

	Mat4 Transform::getMat() {
		Mat4 t(1.0);
		t._03 = p.x;
		t._13 = p.y;
		t._23 = p.z;
	
		Mat4 _s(1.0);
		_s._00 = s.x;
		_s._11 = s.y;
		_s._22 = s.z;

		Mat4 r = o.toMat();

		return _s * t * r;
	}

	void Transform::move(float x, float y, float z) {
		p.x += x;
		p.y += y;
		p.z += z;
	}

	void Transform::move(Vec3 delta) {
		p = p + delta;
	}

	void Transform::scale(float x, float y, float z) {
		s.x *= x;
		s.y *= y;
		s.z *= z;
	}

	void Transform::scale(Vec3 _scale) {
		s.x *= _scale.x;
		s.y *= _scale.y;
		s.z *= _scale.z;

	}

	void Transform::rotateX(float angle) {
		Quat r(Vec3(1, 0, 0), angle);
		o = o * r;
	}

	void Transform::rotateY(float angle) {
		Quat r(Vec3(0, 1, 0), angle);
		o = o * r;
	}

	void Transform::rotateZ(float angle) {
		Quat r(Vec3(0, 0, 1), angle);
		o = o * r;
	}
}
