#pragma once
#include "math.h"

namespace hate {
	/**
	 * A camera can be used to create the
	 * illusion that player is moving.
	 *
	 * FOV is assumed to be in radians.
	 */
	class Camera {
		public:
			Vec3 position;
			Quat orientation;
			float fov;
			float aspect = 16.0 / 9.0;

			float near = 0.1f;
			float far = 100;

			Camera(float _fov = M_PI / 2);

			~Camera();

			/**
			 * Generates a projection matrix
			 * based on the information stored in the camera.
			 */
			Mat4 getProjection();

			/**
			 * Generates the world transform
			 * for the camera.
			 */
			Mat4 getWorld();
	};
}
