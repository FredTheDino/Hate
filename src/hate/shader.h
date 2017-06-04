// 
// A shader is a program that runs on the CPU,
//
// This here is an interface to it that keeps
// track of some stuff for you to make life
// a little bit easier.
//
#pragma once
#include <string>
#include "basic.h"

namespace hate {
	// The shader struct 
	struct shader {
#ifdef DEBUG
		long edit_time = 0;
		float timer = 0;
#endif
		GLuint program;
		std::string path;
	};

	// Loads a shader onto the graphics card from
	// two text files.
	// 		/path/to/file.vert
	// 		/path/to/file.frag
	extern shader load_shader(std::string path);

	// Clears a shader from memory by letting
	// OpenGL dealocate it.
	extern void delete_shader(shader s);

	// Uses the program
	//
	// (I dislike that the shader is passed
	// by refference, it isn't uniform with
	// the rest of the program... But it is
	// needed for the hot-swapable shader.)
	extern void use_shader(shader& s);
}
