#include "hate.h"
#include "entity.h"
#include "entity.cpp"
#include "component.h"
#include <unistd.h>
#include <iostream>
#include <exception>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace hate {

	Hate*   Hate::CORE   = nullptr;
	Loader* Hate::LOADER = new Loader();
	
	Hate::Hate(void(*load)(void), void(*clean)(void)) {
		CORE = this;
		this->load = load;
		this->clean = clean;
		
		// Inital setup
		running = true;

		if (!glfwInit()) {
			throw std::runtime_error("Failed to initalize GLFW\n");
		}	
		window = new Window(0u, 0u);

		if (glewInit()) {
			throw std::runtime_error("Failed to initalize GLEW\n");
		}

		// Call load
		(*this->load)();

		// Show the window if the user has loaded a config or whatever
		window->show();

		loop();
	}

	Hate::~Hate() {
		// Let the user unallocate stuff
		(*this->clean)();

		// Unalocate the engine
		delete window;
	}

	void Hate::loop() {
		Entity e;
		e.add(new Component());
		while (running) {
			window->update();

			glBegin(GL_TRIANGLES);
			glColor3f(0.3, 0.2, 0.1);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(0, 1, 0);
			glEnd();

			running = !window->shouldClose();
		}
	}
}
