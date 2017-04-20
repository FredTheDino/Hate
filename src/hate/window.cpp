#include "window.h"

namespace Hate {

	Window::Window(int width, int height, const char* title, int monitor) {
		int monitor_count = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
		// If you have selected an invalid monitor, use the default
		int m = 0;
		if (monitor_count >= monitor) {
			m = monitor;
		}
		
		// Get the mode
		const GLFWvidmode* mode = glfwGetVideoMode(monitors[m]);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		glfw_window = glfwCreateWindow(width, height, title, monitors[m], NULL);
	}

	Window::~Window() {
		glfwDestroyWindow(glfw_window);
	}
}
