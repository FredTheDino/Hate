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
	float window_aspect_ratio;

	// Callbacks
	void close_callback(GLFWwindow* window) {
		running = false;
	}

	void resize_callback(GLFWwindow* window, int new_width, int new_height) {
		window_width = new_width;
		window_height = new_height;

		window_aspect_ratio = (float) new_width / new_height;

		glViewport(0, 0, new_width, new_height);
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mouse_position.x = xpos;
		mouse_position.y = ypos;
	}

	void make_window() {
		if (!glfwInit()) 
			printf("Failed to initalze GLFW - Window and IO library\n");

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL); // Not sure I like these hard constants, might be better to pass this stuff in via a struct.
		window_width = WINDOW_WIDTH;
		window_height = WINDOW_HEIGHT;
		window_aspect_ratio = (float) window_width / window_height;
		
		glfwSetWindowSizeLimits(window, 600, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowCloseCallback(window, close_callback);
		glfwSetWindowSizeCallback(window, resize_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		// For GLEW, turns out this is important
		glfwMakeContextCurrent(window);	

		// @FIXME, we currently set Vsync to true, allways... 
		// Maybe not do that? And the clear color... We need 
		// some sort of initalizer object.
		glfwSwapInterval(1);
	}

	void init_hate() {
		// Those don't really have dependancies.
		find_resource_location();
		load_input_map("input.map"); // Load that map!

		// GLFW stuff.
		make_window();

		// This needs a window
		init_graphics();
		
		// Set up that audio!
		init_audio();
	}

	void destory_hate() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void run_hate() {

		texture te = load_texture("monkey_norm.png", false);
		texture t2 = load_texture("torus_norm.png", false);
		shader s = load_shader("master.glsl");

		auto sound_file = load_wav("a.wav");
		play_sound(sound_file, MUSIC);

		use_shader(s);
		int w, h;
		glfwGetWindowSize(window, &w, &h);

		float y = 0;

		font f = load_font("fonts/droid_sans");
		
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
				cam.position.x -= get_clock_delta();

			if (is_down("right"))
				cam.position.x += get_clock_delta();

#ifdef DEBUG
			reload_input_map("input.map", true);
			recompile_shader(&s, true);
#endif
			cam.position.y = sin(get_clock_time());
			use_shader(s);
			use_projection(cam);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, te.tex_id);
			draw_color(vec4(0.74, 0.2, 0.6, 1.0));
			glUniform1i(11, 0);
			draw_sprite(0, y, 1, 1, &te, &te);

			draw_sprite(0.1, cos(get_clock_time()) * 0.5, 1, 1, &t2, &t2);

			//printf("to_gl: %f, %f\n", mouse_to_gl().x, mouse_to_gl().y);
			draw_sprite(mouse_to_gl().x, mouse_to_gl().y, 0.2, 0.2, &t2, &t2, 0, false);

			float size = 3 + sin(get_clock_time());
			std::string text = "WOAH!?"; //"FPS: " + std::to_string(get_clock_fps());
			float text_width = get_length_of_text(text, size, f);
			draw_text(text, size, f, sin(get_clock_time()) - text_width / 2, 0, vec4(1.0, sin(get_clock_time()), 0.5, 1.0));
			
			// Updates the graphics
			glfwSwapBuffers(window);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		delete_sound(sound_file);
		delete_font(f);
		delete_texture(te);
		delete_texture(t2);
		delete_shader(s);
	}
}
