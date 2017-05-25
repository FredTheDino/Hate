#include "clock.h"
#include "platform.h"

namespace hate {
	Clock::Clock() {
		t = 0;
		zero();
	}

	void Clock::zero() {
		glfwSetTime(0);
	}

	double Clock::getDelta() {
		if (delta > maxDelta && maxDelta != 0)
			return maxDelta;
		return delta;
	}

	double Clock::getTime() {
		return t;
	}

	int Clock::getFPS() {
		return frames;
	}

	void Clock::update() {
		static double timer = 0;
		static int frames = 0;
		double t1 = glfwGetTime();
		
		delta = t1 - t;

		frames++;
		timer += delta;
		if (timer > 1) {
			timer -= 1;
			this->frames = frames;
			frames = 0;
		}

		t = t1;
	}
}
