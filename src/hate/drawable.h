#pragma once
#include <vector>
#include "texture.h"
#include "mesh.h"
#include "math.h"


#define _DRAWABLE_
namespace hate {
	enum TextureName {
		DIFFUSE,
		SPECULAR,
		NORMAL,
		NUM_TEXTURES
	};

	/**
	 * This is a component that can be drawn.
	 * They should each implement the drawing function.
	 */
	class Drawable {
		public:
			// Constructs a new drawable
			Drawable();
			Drawable(const char* path, int layer=0);
			Drawable(std::string path, int layer=0);

			// Destructor
			~Drawable();

			void init(std::string path, int layer=0);

			/**
			 * Sets the layer for drawing.
			 * No matter who you are, use this function instead of 
			 * setting the layer yourself
			 */
			void setLayer(int l);

			/**
			 * If the drawable can be drawn
			 * or not. Base implementation
			 * checks if there is a mesh.
			 */
			bool canDraw();

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
			 *
			 * By default this uses a simple orthographic shader,
			 * but this can also be over written.
			 */
			void draw(Mat4 m);

			Texture* textures[NUM_TEXTURES];

		private:
			// The layer is the draworder of the drawables.
			// If two drawables share a layer the order is not specified.
			int layer;

			// The mesh the drawable should use.
			Mesh* mesh = nullptr;

			// If the drawable has been initalized.
			bool initalized = false;
	};
}
