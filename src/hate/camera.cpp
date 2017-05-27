#include "camera.h"

namespace hate {

	Camera::Camera(float _fov) {
		fov = _fov;
	}

	Camera::~Camera() {}

	Mat4 Camera::getProjection() {
		float zoom = 1 / tan(fov);
		float fn = far - near;
		Mat4 p(1.0);
		p._00 = zoom / aspect;
		// OpenGL is upside down, it's offical.
		p._11 = -zoom;
		p._22 = - far / fn;
		p._23 = -1;
		p._32 = - far * near / fn;

		return p;
	}

	Mat4 Camera::getWorld() {
		Mat4 t(1.0);
		t._03 = position.x;
		t._13 = position.y;
		t._23 = position.z;

		Mat4 r = orientation.toMat();

		return r * t;
	}
	
}
