#include "basic.h"
#include <vector>
#include <fstream>
#include "core.h"
#include "math.h"
#include "misc.h"
#include "loader.h"
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

	camera cam;

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

	// Who doesn't want to use a camera
	void use_projection(camera c) {
		mat4 p = ortho_project(c.position, (float) window_width / (float) window_height, c.zoom);
		// Don't know if this works!
		glUniformMatrix4fv(8, &p._01 - &p._00, GL_FALSE, &p._[0]);
	}

	// FONTS
	
	// Loads a font.
	font load_font(std::string path) {
		// Load in the texture.
		font f;
		f.tex = load_texture(path + ".png");

		// Parse the .fnt file
		std::ifstream file;
		file.open(get_real_path(path + ".fnt"));

		if (!file) {
			// Errors?
		}

		std::string line;
		while (std::getline(file, line)) {
			auto parse = split(line);

			// We only care about the "char", the rest is allready known.
			if (parse[0] != "char") continue;

			float w, h;
			w = 1 / (float) f.tex.w;
			h = 1 / (float) f.tex.h;

			face font_face;
			// @Performance: When the character isn't needed to be drawn, 
			// it's set to 0 in everything but adavnce and id. We could
			// skipp parseing the rest of the line.
			font_face.id = stoi(split(parse[1], '=')[1]);
			font_face.u =  stoi(split(parse[2], '=')[1]) * w;
			font_face.v =  stoi(split(parse[3], '=')[1]) * h;
			font_face.w =  stoi(split(parse[4], '=')[1]) * w;
			font_face.h =  stoi(split(parse[5], '=')[1]) * h;
			font_face.offset_x = 
			      stoi(split(parse[6], '=')[1]) * w;
			font_face.offset_y = 
			      stoi(split(parse[7], '=')[1]) * h;
			font_face.advance = 
			      stoi(split(parse[8], '=')[1]) * w;

			// There, wasn't that hard was it?
			f.faces[font_face.id] = font_face;
		}
		
		return f;
	}

	GLuint text_vbo = -1;
	GLuint text_vao = -1;

	// Renders a pice of text with the specified font to the screen.
	void draw_text(std::string text, float size, font& f, float x, float y) {
		std::vector<vertex> verticies;
		verticies.reserve(text.size() * 6);

		// Generate the mesh with coordinates.
		float cur = x;
		for (char c : text) {
			// ff stands for font face
			face ff = f.faces[c];

			if (ff.h != 0) {
				float bx   = cur + ff.offset_x * size;
				float bx_n = bx + ff.w * size;

				float by   = ff.offset_y * size;
				float by_n = by + ff.h * size;

				float u    = ff.u;
				float u_n  = u + ff.w;

				float v    = ff.v;
				float v_n  = v + ff.h;

				verticies.push_back(vertex(bx  , by_n, u  , v_n));
				verticies.push_back(vertex(bx  , by  , u  , v));	
				verticies.push_back(vertex(bx_n, by_n, u_n, v_n));
				verticies.push_back(vertex(bx  , by  , u  , v));
				verticies.push_back(vertex(bx_n, by  , u_n, v));
				verticies.push_back(vertex(bx_n, by_n, u_n, v_n));
			}
			
			cur += ff.advance * size;
		}

		// Get ready to render!
		if (text_vao == -1) {
			glGenVertexArrays(1, &text_vao);
			glGenBuffers(1, &text_vao);
		}

		// Assumes the master shader is used.
		
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, f.tex.tex_id);
		glUniform1i(10, 1);

		glUniform1i(12, 1);
		glUniform1f(13, 1.0);
		glBindVertexArray(text_vao);
		{
			glBindBuffer(GL_ARRAY_BUFFER, text_vbo);
			glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(vertex), 
					&verticies[0], GL_DYNAMIC_DRAW);

			// Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
					sizeof(vertex), (GLvoid*) offsetof(vertex, position));

			// Texture coordinate
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 
					sizeof(vertex), (GLvoid*) offsetof(vertex, uv));
		}
		// Draw
		glDrawArrays(GL_TRIANGLES, 0, verticies.size());

		glBindVertexArray(0);
		// Reset the state.
		glUniform1i(12, 0);
	}

	// Gets the length of the text in the coordinate space with the specified
	// size.
	float get_length_of_text(std::string text, float size, font& f) {
		float total_length = 0;

		for (char c : text) {
			total_length += f.faces[c].advance * size;
		}

		return total_length;
	}


}
