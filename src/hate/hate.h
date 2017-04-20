#pragma once
#include "window.h"

namespace Hate {
	/**
	 * The core class for using the Hate-Engine
	 */
	class Hate {
		public:
			/**
			 * Creates a new Hate engine object.
			 * @param *load the load function that loads when the game is started.
			 * @param *clean the function that cleans when the game is closed.
			 */
			Hate(void(*load)(void), void(*clean)(void));

			// Virtual destructor for completeness
			~Hate();

			/**
			 * The main loop of the engine.
			 * Loops through and updates all the entities in the engine.
			 */
			void loop();

			// A static refference to the core
			static Hate* CORE;
		private:
			/**
			 * The function that handles the loading of resources.
			 * This function is user defined.
			 */
			void (*load)(void);

			/**
			 * The function that handles the cleaning of the resources.
			 * This function is user defined.
			 */
			void (*clean)(void);

			// If the engine is in a running state.
			bool running;
			// A refference to the currentl window.
			Window* window;
	};
}
