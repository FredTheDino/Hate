#include <vector>
#include "mesh.h"
#include "platform.h"

namespace hate {

	void Mesh::init() {
		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		std::vector<Vertex> verticies;
		verticies.push_back(Vertex(0, 0, 0, 0));
		verticies.push_back(Vertex(1, 0, 0, 0));
		verticies.push_back(Vertex(1, 1, 0, 0));
		verticies.push_back(Vertex(0, 1, 0, 0));

		std::vector<GLuint> indicies;
		indicies.push_back(0);
		indicies.push_back(1);
		indicies.push_back(2);
		indicies.push_back(2);
		indicies.push_back(0);
		indicies.push_back(3);

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
			glVertexAttribPointer(0, 2, GL_FALSE, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			
			// Position
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FALSE, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texCoord));
		}
		glBindVertexArray(0);
	}

	Mesh::Mesh() {
		init();
	}

	Mesh::~Mesh() {
		
	}

	void Mesh::draw() {
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, drawLength, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
