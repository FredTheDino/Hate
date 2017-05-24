#pragma once
#include "platform.h"

namespace hate {
	/**
	 * An OpenGL mesh.
	 */
	class Mesh {
		public:
			/**
			 * Creates a new OpenGL mesh
			 * that is cached on the graphicscard.
			 */
			Mesh() {}

			/**
			 * Deletes the data stored locally.
			 */
			~Mesh() {}

			/**
			 * Cleans up the graphicscard so
			 * there aren't a bunch of unallocated 
			 * meshs floating about.
			 */
			void clean() {}

			/**
			 * Binds the mesh to the specified
			 * slot for the shader to use.
			 */
			void bind(int slot) {
				
			}

		private:
			// The OpenGL id of the VBO.
			int vbo;
			
			// The OpenGL id of the VAO.
			int vao;
	};
}
