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
		unsigned long long edit_time = 0;
		GLuint program;
		std::string path;
	};

	// Loads a shader onto the graphics card from
	// two text files.
	// 		/path/to/file.vert
	// 		/path/to/file.frag
	extern shader load_shader(std::string path);

	// Uses the program
	extern void use_program(shader s);
}
