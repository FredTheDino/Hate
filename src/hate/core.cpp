#include "core.h"
#include "graphics.h"
#include "loader.h"
#include "shader.h"
#include <stdio.h>
#include <cmath>
#include <string>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400
#define WINDOW_TITLE  "Hello World"

namespace hate {
	// Declaration
	bool running = true;
	GLFWwindow* window = nullptr;

	void close_callback(GLFWwindow* window) {
		running = false;
	}

	void init_hate() {
		// GLFW stuff.
		if (!glfwInit()) 
			printf("Failed to initalze GLFW - Window and IO library\n");

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL); // Not sure I like these hard constants, might be better to pass this stuff in via a struct.
		glfwSetWindowCloseCallback(window, close_callback);
		
		// For GLEW, turns out this is important
		glfwMakeContextCurrent(window);	

		// @FIXME, we currently set Vsync to true, allways... Maybe not do that? And the clear color... We need to fix some stuff here...
		glfwSwapInterval(1);

		find_resource_location();

		if (glewInit())
			printf("Failed to initalize GLEW - Extension Wrangler\n");
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glSampleCoverage(1.0, GL_TRUE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		init_graphics();
	}

	void destory_hate() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void run_hate() {
		texture te = load_texture("monkey_norm.png", false);
		shader s = load_shader("master.glsl");

		use_shader(s);
		int w, h;
		glfwGetWindowWidth(window, &w);
		glfwGetWindowHeight(window, &h);
		
		while (running) {
			glfwPollEvents();
			glfwSwapBuffers(window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef DEBUG
			use_shader(s);
#endif

			float t = glfwGetTime();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, te.tex_id);
			glUniform1i(11, 0);
			draw_quad(0, 0, 1, 1);
		}
	}
}
