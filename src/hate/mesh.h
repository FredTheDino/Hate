#pragma once
#include "platform.h"
#include "math.h"

namespace hate {
	struct Vertex {
		Vec2 position;
		Vec2 texCoord;

		Vertex(float x, float y, float u, float v) {
			position = Vec2(x, y);
			texCoord = Vec2(u, v);
		}
	};


	/**
	 * An OpenGL mesh.
	 */
	class Mesh {
		public:
			/**
			 * Creates a new OpenGL mesh
			 * that is cached on the graphicscard.
			 */
			Mesh();

			/**
			 * Deletes the data stored locally.
			 */
			~Mesh();

			/**
			 * Cleans up the graphicscard so
			 * there aren't a bunch of unallocated 
			 * meshs floating about.
			 */
			void clean();

			/**
			 * Draws the mesh
			 */
			void draw();

		private:
			// Initalizes the mesh
			void init();

			// How many verticies should be draw.
			unsigned int drawLength;

			// The OpenGL id of the VBO.
			GLuint vbo,
			// The OpenGL id of the VAO.
			vao,
			// The OpenGL indicies.
			ebo;
	};
}
