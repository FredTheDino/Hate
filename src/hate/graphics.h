//
// The graphics file is for drawing things to the screen.
// It supports drawing squares, with and without textures
// by default.
//
#pragma once
#include "matrix.h"
#include <unordered_map>

namespace hate {
	// STRUCTS
	
	// A struct for keeping track of the
	// camera.
	struct Camera {
		Vec2 position = Vec2(0, 0);
		float zoom = 1.0f;
		// Disabled for now.
		//float rotation = 0;
	};

	// A texture class that holds a texture.
	struct Texture {
		int w, h;
		unsigned short tex_id;
		unsigned char sprites_x = 1;
		unsigned char sprites_y = 1;
	};
	
	// A nice bundle of data related to 
	// meshes. 
	struct Mesh {
		unsigned vbo;
		unsigned vao;
		unsigned ebo = 0;
		unsigned draw_count;
	};

	// This data type corresponds to a single face, that
	// can be drawn to the screen.
	struct Font_Face {
		unsigned int id = 0;
		// The start of the quad.
		float u, v = 0;
		// The size of the quad.
		float w, h = 0;
		// The offsets
		float offset_x, offset_y = 0;
		// How long until the next char.
		float advance = 0;
	};

	// This is all the data of a single
	// font stored into one nice container.
	struct Font {
		// Storing them sorted since it isn't
		// losely populated.
		std::unordered_map<char, Font_Face> faces;
		float highest;
		float lowest;
		// The texture holding all the baked fonts.
		Texture tex;
	};
	
	// FONTS
	
	// Loads a font from a prebaked .fnt and .png file
	// that share name.
	//
	// The file types should be ommited in the path.
	extern Font load_font(std::string path);

	// Clears the font data so OpenGL doens't get mad.
	extern void delete_font(Font& f);
	
#define MIN_EDGE 0.48f
#define MAX_EDGE 0.5f
	// Renders a pice of text with the specified font to the screen.
	extern void draw_text(std::string text, float size, Font const& f, 
			float x, float y, Vec4 color = Vec4(0, 0, 0, 1.0), 
			float spacing = 1.0f, 
			bool use_transform = true, float min_edge = MIN_EDGE, float max_edge = MAX_EDGE);

	// Generates a mesh with the specified text in the font.
	//
	// This procedure is also called by "draw_text", but
	// this allows you to make optemizations, like not 
	// re generating the text if it is the same as last frame.
	Mesh generate_text_mesh(std::string text, float size, Font const& f, 
			float x, float y, float spacing = 1.0f);

	// Draws the generated text_mesh.
	void draw_text_mesh(Mesh m, Font const& f, 
			Vec4 color = Vec4(0, 0, 0, 1.0), 
			bool use_transform = true, float min_edge = MIN_EDGE, float max_edge = MAX_EDGE);

	// Deletes a mesh, suprise...
	void delete_mesh(Mesh m);

	// Gets the length of the text in the coordinate space with the specified
	// size.
	extern float get_length_of_text(std::string text, float size, Font const& f, float spacing = 1.0f);

	// Returns the height of the font, which is the distance from the base line to the highest.
	extern float get_highest_of_font(float size, Font const& f);

	// Returns the lowest point on the font.
	extern float get_lowest_of_font(float size, Font const& f);

	// GENERAL RENDERING

	// The global and standardlyused camera.
	extern Camera cam;

	// Sends in the camera matrix.
	extern void use_projection(Camera c);

	// This draws a mesh, any mesh.
	void draw_mesh(Mesh m);

	// Initalizes the graphics, by registering some basic
	// meshes and initalizeing the shaders on the graphics card.
	//
	// This is called by the other init calls in the engine, and
	// should not be called. Since it probably won't do anything
	// except add some bloat to the graphcis cards memory.
	extern void init_graphics();

	// If you want to bind a texture to it.
	extern void draw_sprite(float x, float y, float w, float h, Texture* color, Texture* normal = nullptr, int sub_sprite = 0, bool translate = true);
	extern void draw_sprite(Mat4 m, Texture* color, Texture* normal = nullptr, int sub_sprite = 0, bool translate = true);

	// Specifies the color for these meshes.
	extern void draw_color(Vec4 color);

	// Draws a rectangle in a previousely specified color.
	extern void draw_quad(float x, float y, float w, float h, bool translate = true);
	extern void draw_quad(Mat4 transform, bool translate = true);
}
