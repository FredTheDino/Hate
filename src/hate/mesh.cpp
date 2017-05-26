#include <vector>
#include "mesh.h"
#include "platform.h"

namespace hate {

	void Mesh::init(std::vector<Vertex>& verticies,  std::vector<GLuint>& indicies) {
		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		drawLength = indicies.size();

		glBindVertexArray(vao);
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), 
					&verticies[0], GL_STATIC_DRAW);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), 
					&indicies[0], GL_STATIC_DRAW);

			// Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			
			// Normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));
			
			// Texture coordinate
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texCoord));
		}
		glBindVertexArray(0);
	}

	Mesh::Mesh() {}

	Mesh::~Mesh() {}

	void Mesh::clean() {
		printf("Clean up after mesh?\n");
	}

	void Mesh::draw() {
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, drawLength, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}
