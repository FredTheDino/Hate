#include "hate.h"
#include "entity.cpp"
#include "drawable.h"
#include "platform.h"
#include "mesh.h"
#include <iostream>
#include <exception>

namespace hate {

	// Globals
	Hate*     	 	Hate::CORE    = nullptr;
	Loader* 		Hate::LOADER  = nullptr;
	RenderEngine*	Hate::ENGINE   = nullptr;
	Shader*		 	Hate::SHADER  = nullptr;
	Clock* 		 	Hate::CLOCK   = nullptr;

	Hate::Hate(void(*load)(void), void(*clean)(void)) {
		// These can be set here.
		CORE = this;
		LOADER = new Loader();
		printf("loader: %p\n", LOADER);
		this->load = load;
		this->clean = clean;

		// Inital setup
		running = true;

		if (!glfwInit()) {
			throw std::runtime_error("Failed to initalize GLFW\n");
		}	

		window = new Window(0u, 0u);
		window->setSwapInverval(1);

		if (glewInit()) {
			throw std::runtime_error("Failed to initalize GLEW\n");
		}

		// These need OpenGL
        ENGINE = new RenderEngine();
		SHADER = new Shader("master.glsl");
		CLOCK  = new Clock();

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
		delete SHADER;
		delete CLOCK;
	}

	void Hate::loop() {
		Entity* e = new Entity();
		e->add(new Drawable(5));

		CLOCK->zero();

		Mesh m;
		double delta = 0;
		double timer = 0;
		while (running) {
			window->update();
			running = !window->shouldClose();

			CLOCK->update();
			delta = CLOCK->getDelta();

			timer += delta;
			if (timer > 1) {
				timer -= 1;
				printf("FPS: %i\n", CLOCK->getFPS());
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			ENGINE->draw();

#ifdef DEBUG
			// Check the shader if it has changed
			SHADER->recompileIfChanged();
#endif

			SHADER->bind();

			m.draw();
		}

		delete e;
	}
}
