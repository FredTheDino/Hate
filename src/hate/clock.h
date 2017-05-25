#pragma once

namespace hate {
	class Clock {
	public:	
		Clock();

		/**
		 * Zeroes out the clock.
		 */
		void zero();

		/**
		 * Returns the time between this and the last frame.
		 */
		double getDelta();

		/**
		 * Returns the time since the last zero.
		 */
		double getTime();

		/**
		 * Updates the clock, shouldn't be 
		 * called by the user.
		 */
		void update();

		/**
		 * The number of frames passed in one second.
		 */
		int getFPS();

	private:
		// The current time
		double t;

		// The time since last update.
		double delta;

		// A frame counter to give accurate FPS.
		int frames;

		// A way to limit that too much happens in one frame.
		double maxDelta = 1 / 10;
	};
}
