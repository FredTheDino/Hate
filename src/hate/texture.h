#pragma once
#include "platform.h"

namespace hate {
	/**
	 * An OpenGL texture.
	 */
	class Texture {
		public:
			/**
			 * Creates a new OpenGL texture
			 * that is cached on the graphicscard.
			 */
			Texture() {}

			/**
			 * Deletes the data stored locally.
			 */
			~Texture() {}

			/**
			 * Cleans up the graphicscard so
			 * there aren't a bunch of unallocated 
			 * textures floating about.
			 */
			void clean() {}

			/**
			 * Binds the texture to the specified
			 * slot for the shader to use.
			 */
			void bind(int slot) {
				
			}

		private:
			// The OpenGL id of the texture.
			int id;
	};
}
