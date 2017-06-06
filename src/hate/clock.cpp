#include "clock.h"
#include "basic.h"

namespace hate {

	// What you want to look at.
	float time = 0;
	float delta = 0;
	float fps = 0;

	// For counting FPS
	int frames = 0;
	float frame_timer = 0;
	float last_time = 0;

	void reset_clock() {
		time = glfwGetTime();
		frames = 0;
		frame_timer = 0;
	}

	void update_clock()  {
		float t = glfwGetTime();
		delta = t - time;
		time = t;

		frames++;
		frame_timer += delta;
		if (frame_timer > 1) {
			fps = frames / 1.0f;

			frames = 0;
			frame_timer -= 1.0;
		}
	}	

	float get_clock_delta() {
		return delta;
	}

	float get_clock_time() {
		return time;
	}

	float get_clock_fps() {
		return fps;
	}
}
