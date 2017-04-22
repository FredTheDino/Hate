#pragma once
#include <unordered_map>
#include <vector>
#include "hate.h"
#include "drawable.h"

namespace hate {
	/**
	 * The renderengine handles the drawing of components
	 * that extend the "drawable" component. These components
	 * are put into buckets which are layers which are passed 
	 * into the shader if you want to implement your own paralax.
	 * 
	 * This class should not be implemented by the user since the 
	 * static memeber "hate::Hate::RENDER_ENGINE" is used by the 
	 * engine.
	 * 
	 */
	class RenderEngine() {
		friend Hate;
		protected:
			// Creates a new RenderEngine
			RenderEngine();

			// Cleans up after the RenderEngine
			~RenderEngine();

		public:
			/**
			 * Adds the specified component to drawable lists for the RenderEngine.
			 *
			 * If the one you want to add already exists, it will be added again and
			 * will maybe cause a nullptr exception since only the first one will be 
			 * deleted. You should therefore not call this function here, call it on
			 * the drawable.
			 * 
			 * @param the drawable you want to add.
			 */
			void add(Drawable* drawable);

			/**
			 * Removes the drawable from list of drawables.
			 * No error is thrown if it cannot be added.
			 *
			 * Will only remove the first instance.
			 *
			 * @param drawable the drawable you want to add.
			 */
			void remove(Drawable* drawable);

			/**
			 * Renders everything in the render engine.
			 */
			void render();

		private:
			// The layers for rendering
			std::unordered_map<int, std::vector<Drawable*>> layers;

	}
}
