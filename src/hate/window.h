#pragma once
#include <string>

class GLFWwindow;
namespace hate {
	/**
	 * Makes the creaton of windows easier and wraps it in
	 * a class for object oriented goodness.
	 */
	class Window {
		public:
			
			/**
			 * Creates a new window.
			 * The window is created according to specifications of your monitor
			 * if you don't specify anything.
			 *
			 * @param title the title of the window. ("Unnamed")
			 * @param monitor the id of the monitor you want to display on. (0)
			 * @param fullscreen if the window should be fullscreen or not. (true)
			 */
			Window(const char* title="Unnamed", unsigned int monitor=0, bool fullscreen=true);

			/**
			 * Creates a new window.
			 * The window is created according to the specifications
			 * of your monitor and what you pass into the function.
			 * 
			 * @param width the width of the new window. (Screenwidth / 2)
			 * @param height the height of the new window. (Sreenheight / 2)
			 * @param title the title of the window. ("Unnamed")
			 * @param monitor the id of the monitor you want to display on. (0)
			 */
			Window(unsigned int width, unsigned int height, const char* title="Unnamed", unsigned int monitor=0, bool fullscreen=false);

			/**
			 * Cleans up after the window.
			 * Makes sure there are no allocated resources that should be unalocated.
			 */
			~Window();

			/**
			 * Updates the window by pulling events and swaping the buffer.
			 */
			void update();

			/**
			 * If the window has recived a close request or not.
			 */
			bool shouldClose();

			/**
			 * Sets the window to visible.
			 */
			void show();

			/**
			 * Hides the window.
			 */
			void hide();
			
			/**
			 * Sets the size of the window.
			 * @param width the width of the window.
			 * @param height the height of the window.
			 */
			void setSize(unsigned int width, unsigned int height);

			/**
			 * Returns the size of the window.
			 * @param width a pointer to a variable that will be written over with the width.
			 * @param height a pointer to a variable that will be written over with the width.
			 */
			void getSize(int* width, int* height);

			/**
			 * Sets the title of the window.
			 * @param title the new title.
			 */
			void setTitle(const char* title);

			/**
			 * Sets the position of the window.
			 * @param x the x position of the window.
			 * @param y the y position of the window.
			 */
			void setPosition(int x, int y);

			/**
			 * Gets the window position.
			 * @param x the window x position.
			 * @param y the window y position.
			 */
			void getPosition(int* x, int* y);

			/**
			 * Sets the icon of the window.
			 * @param path the path to the icon in the resource folder.
			 */
			void setIcon(std::string path);

			/**
			 * Sets the swap interval, same thing as Vsync.
			 */
			void setSwapInverval(int i = 1);

			/**
			 * Returns the GLFWwindow that lies beind this wrapping.
			 * @return the GLFWwinow
			 */
			GLFWwindow* getWindow();

		private:
			// A refference to the GLFW Window that is the actual window
			GLFWwindow* glfw_window;

			// The mode of the display
			bool is_fullscreen;

			// If the window was decorated
			bool is_decorated;
	};
}
