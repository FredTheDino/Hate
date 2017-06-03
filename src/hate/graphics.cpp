#include "basic.h"
#include <vector>
#include "math.h"
#include "graphics.h"

namespace hate {
	// A nice bundle of data related to 
	// meshes. 
	//
	// Maybe it should be exported, but
	// it is hiden away in here for now.
	struct mesh {
		unsigned	vbo;
		unsigned	vao;
		unsigned	ebo;
		unsigned 	draw_count;
	};

	struct vertex {
		vec2 position;
		vec2 uv;

		vertex(float x, float y, float u, float v) {
			position.x = x;
			position.y = y;
			uv.x = u;
			uv.y = v;
		}
	};

	void draw_mesh(mesh m) {
		glBindVertexArray(m.vao);
		glDrawElements(GL_TRIANGLES, m.draw_count, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	mesh new_mesh(std::vector<int> const& indicies, std::vector<vertex> const& verticies) {
		mesh m;
		glGenVertexArrays(1, &m.vao);

		glGenBuffers(1, &m.vbo);
		glGenBuffers(1, &m.ebo);

		m.draw_count = indicies.size();

		glBindVertexArray(m.vao);
		{
			glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
			glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(vertex), 
					&verticies[0], GL_STATIC_DRAW);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(int), 
					&indicies[0], GL_STATIC_DRAW);

			// Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
					sizeof(vertex), (GLvoid*) offsetof(vertex, position));

			// Texture coordinate
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 
					sizeof(vertex), (GLvoid*) offsetof(vertex, uv));
		}
		glBindVertexArray(0);
		return m;
	}

	// Create this on init
	mesh quad;
		
	void init_graphics() {
		std::vector<int> indicies;
		std::vector<vertex> verticies;

		verticies.push_back(vertex(-0.5,  0.5, 0, 1));
		verticies.push_back(vertex(-0.5, -0.5, 0, 0));
		verticies.push_back(vertex( 0.5, -0.5, 1, 0));
		verticies.push_back(vertex( 0.5,  0.5, 1, 1));

		indicies.push_back(0);
		indicies.push_back(1);
		indicies.push_back(3);
		indicies.push_back(1);
		indicies.push_back(2);
		indicies.push_back(3);

		quad = new_mesh(indicies, verticies);
	}

	// This function is nice to have.
	void draw_quad(float x, float y, float w, float h) {
		// Don't use a transform
		glUniform1i(1, 0);

		glUniform1f(2, x);
		glUniform1f(3, y);
		glUniform1f(4, w);
		glUniform1f(5, h);
		draw_mesh(quad);
	}
}
