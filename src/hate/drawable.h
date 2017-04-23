#pragma once
#include "component.h"


#define _DRAWABLE_
namespace hate {
#ifndef _COMPONENT_
	class Component;
#endif
	/**
	 * This is a component that can be drawn.
	 * They should each implement the drawing function.
	 */
	class Drawable : public Component {
		public:
			// Constructs a new drawable
			Drawable();

			// Destructor
			~Drawable();

			// So we can seperate them
			virtual std::string getKey() { return "drawable-base"; };

			/**
			 * Sets the layer for drawing.
			 * No matter who you are, use this function instead of 
			 * setting the layer yourself
			 */
			void setLayer(int l);

			/**
			 * Returns the layer of this drawable.
			 *
			 * The layer determins the draw order, where the lowest layer will
			 * be draw first.
			 */
			int getLayer();

			/**
			 * The draw function that draws the drawable.
			 *
			 * Thie function is made to be overwritten and alows
			 * different kinds of rendering.
			 */
			virtual void draw();

		private:
			// The layer is the draworder of the drawables.
			// If two drawables share a layer the order is not specified.
			int layer;

	};
}
