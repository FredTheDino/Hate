#include "core.h"
#include "graphics.h"
#include "loader.h"
#include "shader.h"
#include "input.h"
#include "clock.h"
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
	int window_width;
	int window_height;

	// Callbacks
	void close_callback(GLFWwindow* window) {
		running = false;
	}

	void resize_callback(GLFWwindow* window, int new_width, int new_height) {
		window_width = new_width;
		window_height = new_height;
	}

	void init_hate() {
		// GLFW stuff.
		if (!glfwInit()) 
			printf("Failed to initalze GLFW - Window and IO library\n");

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL); // Not sure I like these hard constants, might be better to pass this stuff in via a struct.
		window_width = WINDOW_WIDTH;
		window_height = WINDOW_HEIGHT;

		glfwSetWindowCloseCallback(window, close_callback);
		
		// For GLEW, turns out this is important
		glfwMakeContextCurrent(window);	

		// @FIXME, we currently set Vsync to true, allways... 
		// Maybe not do that? And the clear color... We need 
		// some sort of initalizer object.
		glfwSwapInterval(1);

		find_resource_location();

		if (glewInit())
			printf("Failed to initalize GLEW - Extension Wrangler\n");

		// GL Stuff
		//glEnable(GL_DEPTH_TEST); @This is needed on Linux if we want to use it.
		glDisable(GL_DEPTH_TEST); // For safety

		glClearColor(0.0, 0.0, 0.0, 1.0);

		glEnable(GL_MULTISAMPLE); // I don't know if these work...
		glSampleCoverage(1.0, GL_TRUE);

		glEnable(GL_BLEND); // Alpha blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		init_graphics();

		load_input_map("input.map"); // Load that map!
	}

	void destory_hate() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void run_hate() {

		texture te = load_texture("monkey_norm.png", false);
		texture t2 = load_texture("torus_norm.png", false);
		shader s = load_shader("master.glsl");

		use_shader(s);
		int w, h;
		glfwGetWindowSize(window, &w, &h);

		float y = 0;

		font f = load_font("fonts/nimbus");
		
		reset_clock();
		while (running) {
			update_clock();
			// @Tought: glfwPollEvents is in "update_input_map", not sure if it's a good idea.
			update_input_map();

			if (is_down("up")) {
				y += get_clock_delta();
			}

			if (is_down("down")) {
				y -= get_clock_delta();
			}

			if (is_down("left"))
				cam.position.x += get_clock_delta();

			if (is_down("right"))
				cam.position.x -= get_clock_delta();


#ifdef DEBUG
			reload_input_map("input.map", true);
			recompile_shader(&s, true);
#endif
			cam.position.y = sin(get_clock_time());
			use_shader(s);
			use_projection(cam);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, te.tex_id);
			glUniform1i(11, 0);
			draw_quad(0, y, 1, 1);
			glBindTexture(GL_TEXTURE_2D, t2.tex_id);
			draw_quad(0.1, sin(get_clock_time()) * 0.1, 1, 1);

			draw_text("Hello world!", 2, f, -0.5f, 0);
			
			// Updates the graphics
			glfwSwapBuffers(window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		delete_texture(te);
		delete_texture(t2);
		delete_shader(s);
	}
}
