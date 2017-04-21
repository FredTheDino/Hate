#include "window.h"
#include "hate.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

namespace Hate {

	// The close callback for the window
	void close_callback(GLFWwindow* window) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	Window::Window(const char* title, unsigned int monitor, bool fullscreen) 
		: Window(0, 0, title, monitor, fullscreen) {}

	Window::Window(unsigned int width, unsigned int height, const char* title, unsigned int monitor, bool fullscreen) {
		int monitor_count = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
		// If you have selected an invalid monitor, use the default
		if (monitor_count < monitor) {
			monitor = 0;
		}
		
		// Get the mode
		const GLFWvidmode* mode = glfwGetVideoMode(monitors[monitor]);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		if (width == 0 || height == 0) {
			if (fullscreen) {
				width = mode->width;
				height = mode->height;
			} else {
				width = mode->width / 2;
				height = mode->height / 2;
			}
		}

		// Dat readability tho!
		GLFWmonitor* m = fullscreen ? monitors[monitor] : NULL;
		glfw_window = glfwCreateWindow(width, height, title, m, NULL);

		setIcon("icon.png");

		// So we can close it
		glfwSetWindowCloseCallback(glfw_window, close_callback);
		// For GLEW, turns out this is important
		glfwMakeContextCurrent(glfw_window);
	}

	Window::~Window() {
		glfwDestroyWindow(glfw_window);
	}

	void Window::update() {
		glfwPollEvents();
		glfwSwapBuffers(glfw_window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::show() {
		glfwShowWindow(glfw_window);
	}

	void Window::hide() {
		glfwHideWindow(glfw_window);
	}

	void Window::setSize(unsigned int width, unsigned int height) {
		glfwSetWindowSize(glfw_window, width, height);
	}

	void Window::getSize(int* width, int* height) {
		glfwGetWindowSize(glfw_window, width, height);
	}

	void Window::setTitle(const char* title) {
		glfwSetWindowTitle(glfw_window, title);
	}

	void Window::setPosition(int x, int y) {
		glfwSetWindowPos(glfw_window, x, y);
	}

	void Window::getPosition(int* x, int* y) {
		glfwGetWindowPos(glfw_window, x, y);
	}

	void Window::setIcon(std::string path) {
		GLFWimage image;
		unsigned int w, h;

		std::vector<unsigned char> pixels;
		Hate::LOADER->quickLoadPng(path, &w, &h, &pixels);
	
		image.width = w;
		image.height = h;
		image.pixels = &pixels[0];
			
		glfwSetWindowIcon(glfw_window, 1, &image);
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(glfw_window);
	}

	GLFWwindow* Window::getWindow() {
		return glfw_window;
	}

}
