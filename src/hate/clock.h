// 
// This is basically a wraper for 
// the glfw timer callbacks, but 
// this wraper does give you the 
// delta and average out the fps.
// So I guess it's worth it...
//
#pragma once

namespace hate {
	// Resets the clock
	extern void reset_clock();

	// Updates the clock by making it 
	// take 1 step. Called by the main
	// game loop, so no worries.
	extern void update_clock();

	// Returns the current delta of the frame.
	extern float get_clock_delta();

	// Returns the current time of the clock.
	extern float get_clock_time();

	// Returns the FPS over the last second.
	extern float get_clock_fps();
}
