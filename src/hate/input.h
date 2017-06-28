#pragma once
#include "basic.h"
#include "matrix.h"
#include <string>

namespace hate {
	// Loads the specified input map.
	extern void load_input_map(std::string path);

	// For hotloading the input map, clears everything.
	extern void reload_input_map(std::string path, bool use_timer = false);

	// KEYBOARD AND JOYSTICK

	// Updates the input map, by changeing
	// pressed states to down.
	extern void update_input_map();

	// Checks if they input is down.
	extern bool is_down(std::string name);
	
	// Checks if they input is pressed (Same frame as it is pressed).
	extern bool is_pressed(std::string name);

	// Checks if the input was released this frame.
	extern bool is_released(std::string name);

	// Checks if the input is released.
	extern bool is_up(std::string name);

	// Checks if the input has changed from the last frame, in other
	// words it checks if the key is pressed or released.
	extern bool is_changed(std::string name);

	// MOUSE
	// A nice little reffernce for the mouse position.
	extern Vec2 mouse_position;

	// Returns the mouse position in OpenGL coords.
	extern Vec2 mouse_to_gl();

	// Returns the current coordinate in world space
	// pointed to by the mouse.
	extern Vec2 mouse_to_world();
}
