#include <GL/glew.h>
#include "hate.h"
#include <iostream>
#include <exception>
#include <GLFW/glfw3.h>

namespace Hate {
	Hate* Hate::CORE = nullptr;
	
	Hate::Hate(void(*load)(void), void(*clean)(void)) {
		CORE = this;
		this->load = load;
		this->clean = clean;
		
		// Inital setup
		running = true;
		if (!glfwInit())
			throw std::runtime_error("Failed to initalize GLFW\n");
		window = new Window(800, 600);

		if (glewInit())
			throw std::runtime_error("Failed to initalize GLEW\n");
		
		// Call load
		(*this->load)();
	}

	Hate::~Hate() {
		// Let the user unallocate stuff
		(*this->clean)();

		// Unalocate the engine
		delete window;
	}

	void Hate::loop() {
		while (running) {
			running = false;
		}
	}
}
