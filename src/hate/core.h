//
// The core is the main part of the engine,
// it handles the update loop and pulls
// changes from the last frame. It is in
// other words the heart of the engine.
//
// From here you probably want to call
// the init_hate and run_hate functions. 
// My personal recomendation is to call
// init_hate as soon as possible, since you
// might want to do further initalization 
// after the we have fun things like a window.
//

#pragma once
#include "basic.h"
#include <AL/al.h>

namespace hate {
	// Initalizes the engine,
	// by loading GLEW, and initalizing
	// a hidden window.
	extern void init_hate();

	// Runs the engine, this enters a loop
	// that breaks when the program should 
	// exit, so deinitalize stuff after
	// this call.
	extern void run_hate();

	// The GLFWwindow reffernce that can be
	// used if you want to do stuff like 
	// changeing its size.
	//
	// A word of warning, some callbacks
	// might be set allready, and as such
	// should preferably not be tampered with.
	extern GLFWwindow* window;

	extern int window_width;
	extern int window_height;
	extern float window_aspect_ratio;

	// A flag that controls if the game should
	// keep running or not,
	extern bool running;
}
