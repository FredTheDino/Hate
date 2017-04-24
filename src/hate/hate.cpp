#include "hate.h"
#include "entity.cpp"
#include "drawable.h"
#include <iostream>
#include <exception>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace hate {

	Hate*   		Hate::CORE   = nullptr;
	Loader* 		Hate::LOADER = nullptr; 
	RenderEngine* 	Hate::ENGINE = nullptr; 
	
	Hate::Hate(void(*load)(void), void(*clean)(void)) {
		CORE = this;
		LOADER = new Loader();
        ENGINE = new RenderEngine();
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
		delete LOADER;
		delete ENGINE;
	}

	void Hate::loop() {
		Entity* e = new Entity();
		e->add(new Drawable(5));

		while (running) {
			window->update();
			running = !window->shouldClose();

			ENGINE->draw();

			glBegin(GL_TRIANGLES);
			glColor3f(0.3, 0.2, 0.3);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(0, 1, 0);
			glEnd();
		}

		delete e;
	}
}
