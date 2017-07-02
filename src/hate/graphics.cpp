#include "basic.h"
#include <vector>
#include <fstream>
#include "core.h"
#include "math.h"
#include "misc.h"
#include "loader.h"
#include "graphics.h"

namespace hate {

	// The camera that is normally used.
	Camera cam;

	struct vertex {
		Vec2 position;
		Vec2 uv;

		vertex(float x, float y, float u, float v) {
			position.x = x;
			position.y = y;
			uv.x = u;
			uv.y = v;
		}
	};

	void draw_mesh(Mesh m) {
		glBindVertexArray(m.vao);
		if (m.ebo != 0) {
			glDrawElements(GL_TRIANGLES, m.draw_count, GL_UNSIGNED_INT, 0);
		} else {
			glDrawArrays(GL_TRIANGLES, 0, m.draw_count);
		}
		glBindVertexArray(0);
	}

	Mesh new_mesh(std::vector<vertex> const& verticies) {
		Mesh m;
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

	Mesh new_mesh(std::vector<int> const& indicies, std::vector<vertex> const& verticies) {
		Mesh m;
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

	void delete_mesh(Mesh m) {
		glDeleteVertexArrays(1, &m.vao);
		glDeleteBuffers(1, &m.vbo);

		if (m.ebo) {
			glDeleteBuffers(1, &m.ebo);
		}
	}

	// Create this on init
	Mesh quad;
		
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

	void draw_sprite(Texture* color, Texture* normal, int sub_sprite) {
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

	void draw_sprite(float x, float y, float w, float h, Texture* color, Texture* normal, int sub_sprite, bool translate) {
		// Don't use a transform
		glUniform1i(1, 0);
		glUniform1i(16, translate);

		glUniform1f(2, x);
		glUniform1f(3, y);
		glUniform1f(4, w);
		glUniform1f(5, h);
		
		draw_sprite(color, normal, sub_sprite);
	}

	void draw_sprite(Mat4 m, Texture* color, Texture* normal, int sub_sprite, bool translate) {
		glUniform1i(1, 1);
		glUniform1i(16, translate);

		glUniformMatrix4fv(6, (GLsizei) (&m._01 - &m._00), GL_FALSE, &m._[0]);

		draw_sprite(color, normal, sub_sprite);
	}


	void draw_color(Vec4 color) {
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

	void draw_quad(Mat4 m, bool translate) {
		glUniform1i(1, 1);
		glUniform1i(16, translate);
		glUniform1i(17, 0);

		glUniformMatrix4fv(6, (GLsizei) (&m._01 - &m._00), GL_FALSE, &m._[0]);

		draw_mesh(quad);
	}

	// Who doesn't want to use a camera
	void use_projection(Camera c) {
		Mat4 p = ortho_project(0, window_aspect_ratio, c.zoom);
		Mat4 t = translation(-c.position.x, -c.position.y);
		// Don't know if this works!
		glUniformMatrix4fv(8, (GLsizei) (&p._01 - &p._00), GL_FALSE, &p._[0]);
		glUniformMatrix4fv(7, (GLsizei) (&t._01 - &t._00), GL_FALSE, &t._[0]);
	}

	// FONTS
	
	// Loads a font.
	Font load_font(std::string path) {
		// Load in the texture.
		Font f;
		f.tex = load_texture(path + ".png", true, GL_REPEAT, false);

		// Parse the .fnt file
		std::ifstream file;
		file.open(get_real_path(path + ".fnt"));

		if (!file) {
			// Errors?
		}

		float w, h;
		w = 1 / (float) f.tex.w;
		h = 1 / (float) f.tex.h;

		f.lowest = 100;
		f.highest = 0;

		std::string line;
		while (std::getline(file, line)) {
			auto parse = split(line);

			// We only care about the "char", the rest is allready known.
			if (parse[0] != "char") continue;


			Font_Face font_face;
			// @Performance: When the character isn't needed to be drawn, 
			// it's set to 0 in everything but adavnce and id. We could
			// skipp parseing the rest of the line.
			font_face.id = stoi(split(parse[1], '=')[1]);
			font_face.u  = stoi(split(parse[2], '=')[1]) * w;
			font_face.v  = stoi(split(parse[3], '=')[1]) * h;
			font_face.w  = stoi(split(parse[4], '=')[1]) * w;
			font_face.h  = stoi(split(parse[5], '=')[1]) * h;
			font_face.offset_x = 
			      stoi(split(parse[6], '=')[1]) * w;
			font_face.offset_y = 
			      stoi(split(parse[7], '=')[1]) * h;
			font_face.advance = 
			      stoi(split(parse[8], '=')[1]) * w;

			if (font_face.u != 0 && font_face.v != 0) {
				f.highest = fmax(f.highest, font_face.v + font_face.h);
				f.lowest = fmin(f.lowest, font_face.v);
			}
			f.faces[font_face.id] = font_face;
		}

		f.lowest  *= 0.01f;
		f.highest *= 0.01f;
		
		return f;
	}

	void delete_font(Font& font) {
		delete_texture(font.tex);
		font.faces.clear();
	}

	Mesh generate_text_mesh(std::string text, float size, Font const& font, float spacing) {
		std::vector<vertex> verticies;
		verticies.reserve(text.size() * 6);

		// Generate the mesh with coordinates.
		float cur = get_length_of_text(text, size, font, spacing) / -2;
		float y = get_highest_of_font(size, font) / 2;
		for (char c : text) {
			// ff stands for font face
			Font_Face ff = font.faces.at(c);

			if (ff.h != 0) {
				float bx   = cur + ff.offset_x * size;
				float bx_n = bx + ff.w * size;

				float by   = y + ff.offset_y * size;
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

		Mesh m = new_mesh(verticies);
		return m;
	}

	void draw_text_mesh(Mesh mesh, float x, float y, Font const& font, Vec4 color, bool use_projection, float min_edge, float max_edge) {
		// Assumes the master shader is used,
		// might be dumb...
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, font.tex.tex_id);
		glUniform1i(10, 1);
		glUniform1i(16, use_projection);
		glUniform1i(1, 0); // Don't use a transform matrix

		glUniform1i(12, 1);
		glUniform1f(13, min_edge);
		glUniform1f(14, max_edge);
		glUniform4f(15, color.x, color.y, color.z, color.w);

		glUniform1f(2, x);
		glUniform1f(3, y);

		glUniform1f(4, 1);
		glUniform1f(5, 1);

		draw_mesh(mesh);

		// Reset the state.
		glUniform1i(12, 0);
		glUniform1i(16, 0);
	}

	void draw_text_mesh(Mesh mesh, Mat4 transform, Font const& font, Vec4 color, bool use_transform, float min_edge, float max_edge) {
		// Assumes the master shader is used,
		// might be dumb...
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, font.tex.tex_id);
		glUniform1i(10, 1);
		glUniform1i(16, use_transform);
		glUniform1i(1, 1); // Use a transform matrix

		glUniform1i(12, 1);
		glUniform1f(13, min_edge);
		glUniform1f(14, max_edge);
		glUniform4f(15, color.x, color.y, color.z, color.w);

		glUniformMatrix4fv(6, (GLsizei) (&transform._01 - &transform._00), GL_FALSE, &transform._[0]);

		draw_mesh(mesh);

		// Reset the state.
		glUniform1i(12, 0);
		glUniform1i(16, 0);
	}

	// Renders a pice of text with the specified font to the screen.
	void draw_text(std::string text, float size, Font const& font, 
			float x, float y, Vec4 color, float spacing, 
			bool use_projection, float min_edge, float max_edge) {


		Mesh m = generate_text_mesh(text, size, font, spacing);
		draw_text_mesh(m, x, y, font, color, use_projection, min_edge, max_edge);

		delete_mesh(m);
	}

	// Gets the length of the text in the coordinate space with the specified
	// size.
	float get_length_of_text(std::string text, float size, Font const& font, float spacing) {
		float total_length = 0;

		for (char c : text) {
			auto const& ff = font.faces.at(c);
			total_length += (ff.advance + ff.offset_x) * spacing;
		}

		return total_length * size;
	}

	// Returns the height of the font, which is the distance from the base line to the highest.
	extern float get_highest_of_font(float size, Font const& font) {
		return size * font.highest;
	}

	// Returns the lowest point on the font.
	extern float get_lowest_of_font(float size, Font const& font) {
		return size * font.lowest;
	}
}
