#include <GLFW/glfw3.h>
#include <string>

namespace Hate {
	/**
	 * Makes the creaton of windows easier and wraps it in
	 * a class for object oriented goodness.
	 */
	class Window {
		public:
			/**
			 * Creates a new window.
			 * The window is created according to the specifications 
			 * of your monitor and what you pass into the function
			 * 
			 * @param width the width of the new window (800)
			 * @param height the height of the new window (600)
			 * @param title the title of the window ("Unnamed")
			 * @param monitor the id of the monitor you want to display on (0)
			 */
			Window(int width, int height, const char* title="Unnamed", int monitor=0);

			/**
			 * Cleans up after the window.
			 * Makes sure there are no allocated resources that should be unalocated.
			 */
			~Window();

		private:
			// A refference to the GLFW Window that is the actual window
			GLFWwindow* glfw_window;

			// The dimensions of the display
			int width, height;

			// The mode of the display
			bool is_fullscreen;

			// If the window was decorated
			bool is_decorated;
	};
}
