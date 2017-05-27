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
	Shader*		 	Hate::SHADER  = nullptr;
	Clock* 		 	Hate::CLOCK   = nullptr;
	Camera* 		Hate::CAMERA  = nullptr;
	EntityManager*	Hate::EM 	  = nullptr;

	Hate::Hate(void(*load)(void), void(*clean)(void)) {
		// These can be set here.
		CORE = this;
		LOADER = new Loader();
		CAMERA = new Camera(90);
		EM = new EntityManager();
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
		SHADER = new Shader("master.glsl");
		CLOCK  = new Clock();

		// So this is apparently needed on Linux...
		// It's here as a precaution now.
		glEnable(GL_DEPTH_TEST);

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
		delete SHADER;
		delete CLOCK;
		delete CAMERA;
		delete EM;
	}

	float toRad(float angle) {
		return M_PI / 180 * angle;
	}

	void Hate::loop() {
		Entity* e = new Entity();
		e->drawable = Drawable("suzanne.obj");

		Entity* f = new Entity();
		f->drawable = Drawable("plane.obj");

		f->transform.p.y = -.2;
		f->transform.s.x = 10;
		f->transform.s.y = 10;
	//	f->transform.rotateX(M_PI / 2.0 + 0.2);
		f->transform.o = Quat(Vec3(1, 0, 0), -M_PI / 2);

		CLOCK->zero();
		float timer = 0;
		//Mesh* m = LOADER->loadMesh("suzanne.obj");
		double delta = 0;
		while (running) {
			window->update();
			running = !window->shouldClose();

			CLOCK->update();
			delta = CLOCK->getDelta();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef DEBUG
			// Check the shader if it has changed
			SHADER->recompileIfChanged();
#endif

			//CAMERA->position.y = cos(CLOCK->getTime());
			CAMERA->position.x = sin(CLOCK->getTime());
			CAMERA->position.z = -2;
			//CAMERA->orientation = Quat(Vec3(1, 0, 0), CLOCK->getTime() / 2);

			SHADER->bind();

			e->transform.rotateX(delta);
			e->transform.rotateY(delta);
			e->transform.rotateZ(delta);

			EM->update(delta);
			/*
			e->transform.s.x = 1 + sin(CLOCK->getTime()) * 0.2;
			e->transform.s.y = 1 + sin(CLOCK->getTime() * 0.5f) * 0.2;
			e->transform.p.x = sin(CLOCK->getTime());
			e->transform.p.y = cos(CLOCK->getTime());
			*/
			
			/*Mat4 m = e->transform.getMat();
			e->drawable.draw(m);

			m = f->transform.getMat();
			f->drawable.draw(m);
			*/

			EM->draw();
		}
	}
}
