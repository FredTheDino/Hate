#pragma once
#include "platform.h"
#include "math.h"
#include <vector>

namespace hate {
	struct Vertex {
		Vec3 position;
		Vec3 normal;
		Vec2 texCoord;

		Vertex() {}

		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) {
			position = Vec3(x, y, z);
			normal = Vec3(nx, ny, nz);
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

			// Initalizes the mesh
			void init(std::vector<Vertex>& verticies, std::vector<GLuint>& indicies);

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
