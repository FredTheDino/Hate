#include "core.h"
#include <stdio.h>
#include <string>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "Hello World"

namespace hate {
	// Declaration
	bool running = true;
	GLFWwindow* window = nullptr;

	void close_callback(GLFWwindow* window) {
		running = false;
	}

	void init_hate() {
		printf("We are initalized!\n");

		// GLFW stuff.
		if (!glfwInit()) 
			printf("Failed to initalze GLFW\n");

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL); // Not sure I like these hard constants, might be better to pass this stuff in via a struct.
		glfwSetWindowCloseCallback(window, close_callback);
		
		// For GLEW, turns out this is important
		glfwMakeContextCurrent(window);	

		// @FIXME, we currently set Vsync to true, allways... Maybe not do that? And the clear color... We need to fix some stuff here...
		glfwSwapInterval(1);
		glClearColor(0.2, 0.0, 0.4, 1.0);
		
	}

	void destory_hate() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void run_hate() {
		printf("We are running!\n");
		while (running) {
			glfwPollEvents();
			glfwSwapBuffers(window);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
}
