#include "basic.h"
#include <vector>
#include <fstream>
#include "core.h"
#include "math.h"
#include "misc.h"
#include "loader.h"
#include "graphics.h"

namespace hate {

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
		if (m.ebo != 0) {
			glDrawElements(GL_TRIANGLES, m.draw_count, GL_UNSIGNED_INT, 0);
		} else {
			glDrawArrays(GL_TRIANGLES, 0, m.draw_count);
		}
		glBindVertexArray(0);
	}

	mesh new_mesh(std::vector<vertex> const& verticies) {
		mesh m;
		glGenVertexArrays(1, &m.vao);

		glGenBuffers(1, &m.vbo);

		m.draw_count = verticies.size();

		glBindVertexArray(m.vao);
		{
			glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
			glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(vertex), 
					&verticies[0], GL_STATIC_DRAW);
			

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

	void delete_mesh(mesh m) {
		glDeleteVertexArrays(1, &m.vao);
		glDeleteBuffers(1, &m.vbo);

		if (m.ebo) {
			glDeleteBuffers(1, &m.ebo);
		}
	}

	// Create this on init
	mesh quad;
		
	void init_graphics() {
		// But first we need glew
		if (glewInit())
			printf("Failed to initalize GLEW - Extension Wrangler\n");
		
		// GL default settings.
		printf("[OpenGL] Version: %s\n", glGetString(GL_VERSION));
		printf("[OpenGL] Vendor: %s\n", glGetString(GL_VENDOR));

		//glEnable(GL_DEPTH_TEST); @This is needed on Linux if we want to use it.
		glDisable(GL_DEPTH_TEST); // For safety

		glClearColor(0.0, 0.0, 0.0, 1.0);

		glEnable(GL_MULTISAMPLE); // I don't know if these work...
		glSampleCoverage(1.0, GL_TRUE);

		glEnable(GL_BLEND); // Alpha blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	void draw_sprite(texture* color, texture* normal, int sub_sprite) {
		int draw_mode = 0;
		if (color) 
			draw_mode |= 0b01;
		if (normal)
			draw_mode |= 0b10;

		glUniform1i(17, draw_mode);
		if (color) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, color->tex_id);
			glUniform1i(10, 0);
		}
		if (normal) {
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, color->tex_id);
			glUniform1i(11, 1);
		}

		glUniform1i(20, sub_sprite);
		if (color) {
			glUniform2i(19, color->sprites_x, color->sprites_y);
		} else if (normal) {
			glUniform2i(19, normal->sprites_x, normal->sprites_y);
		}

		draw_mesh(quad);
	}

	void draw_sprite(float x, float y, float w, float h, texture* color, texture* normal, int sub_sprite, bool translate) {
		// Don't use a transform
		glUniform1i(1, 0);
		glUniform1i(16, translate);

		glUniform1f(2, x);
		glUniform1f(3, y);
		glUniform1f(4, w);
		glUniform1f(5, h);
		
		draw_sprite(color, normal, sub_sprite);
	}

	void draw_sprite(mat4 m, texture* color, texture* normal, int sub_sprite, bool translate) {
		glUniform1i(1, 1);
		glUniform1i(16, translate);

		draw_sprite(color, normal, sub_sprite);
	}


	void draw_color(vec4 color) {
		glUniform4f(18, color.r, color.g, color.b, color.a);
	}

	// This function is nice to have.
	void draw_quad(float x, float y, float w, float h, bool translate) {
		// Don't use a transform
		glUniform1i(1, 0);
		glUniform1i(16, translate);
		glUniform1i(17, 0);

		glUniform1f(2, x);
		glUniform1f(3, y);
		glUniform1f(4, w);
		glUniform1f(5, h);
		draw_mesh(quad);
	}

	void draw_quad(mat4 m, bool translate) {
		glUniform1i(1, 1);
		glUniform1i(16, translate);
		glUniform1i(17, 0);

		glUniformMatrix4fv(6, &m._01 - &m._00, GL_FALSE, &m._[0]);
		draw_mesh(quad);
	}

	// Who doesn't want to use a camera
	void use_projection(camera c) {
		mat4 p = ortho_project(0, window_aspect_ratio, c.zoom);
		mat4 t = translation(-c.position.x, -c.position.y);
		// Don't know if this works!
		glUniformMatrix4fv(8, &p._01 - &p._00, GL_FALSE, &p._[0]);
		glUniformMatrix4fv(7, &t._01 - &t._00, GL_FALSE, &t._[0]);
	}

	// FONTS
	
	// Loads a font.
	font load_font(std::string path) {
		// Load in the texture.
		font f;
		f.tex = load_texture(path + ".png", true, GL_REPEAT, false);

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

	void delete_font(font& f) {
		delete_texture(f.tex);
		f.faces.clear();
	}

	mesh generate_text_mesh(std::string text, float size, font& f, float x, float y, float spacing) {
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
			
			cur += (ff.advance + ff.offset_x) * size * spacing;
		}

		mesh m = new_mesh(verticies);
		return m;
		// Draw
		//glDrawArrays(GL_TRIANGLES, 0, verticies.size());
	}

	void draw_text_mesh(mesh m, font& f, vec4 color, float min_edge, float max_edge) {
		// Assumes the master shader is used,
		// might be dumb...
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, f.tex.tex_id);
		glUniform1i(10, 1);

		glUniform1i(12, 1);
		glUniform1f(13, min_edge);
		glUniform1f(14, max_edge);
		glUniform4f(15, color.x, color.y, color.z, color.w);

		draw_mesh(m);

		// Reset the state.
		glUniform1i(12, 0);
	}

	// Renders a pice of text with the specified font to the screen.
	void draw_text(std::string text, float size, font& f, 
			float x, float y, vec4 color, float spacing, 
			float min_edge, float max_edge) {

		// Assumes the master shader is used,
		// might be dumb...
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, f.tex.tex_id);
		glUniform1i(10, 1);

		glUniform1i(12, 1);
		glUniform1f(13, min_edge);
		glUniform1f(14, max_edge);
		glUniform4f(15, color.x, color.y, color.z, color.w);
		mesh m = generate_text_mesh(text, size, f, x, y, spacing);
		draw_mesh(m);
		
		// Reset the state.
		glUniform1i(12, 0);

		delete_mesh(m);

	}

	// Gets the length of the text in the coordinate space with the specified
	// size.
	float get_length_of_text(std::string text, float size, font& f, float spacing) {
		float total_length = 0;

		for (char c : text) {
			auto ff = f.faces[c];
			total_length += (ff.advance + ff.offset_x) * size * spacing;
		}

		return total_length;
	}
}
