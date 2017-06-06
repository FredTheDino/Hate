//
// The graphics file is for drawing things to the screen.
// It supports drawing squares, with and without textures
// by default.
//
#pragma once
#include "math.h"
#include <map>

namespace hate {
	// STRUCTS
	
	// A struct for keeping track of the
	// camera.
	struct camera {
		vec2 position = vec2(0, 0);
		vec2 zoom = vec2(1, 1);
	};

	// A texture class that holds a texture.
	struct texture {
		int w, h;
		unsigned int tex_id;
		int sprites_x = 1;
		int sprites_y = 1;
		int current_sprite = 0;
	};

	// This data type corresponds to a single face, that
	// can be drawn to the screen.
	struct face {
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
	struct font {
		// Storing them sorted since it isn't
		// losely populated.
		std::map<char, face> faces;
		// The texture holding all the baked fonts.
		texture tex;
	};
	
	// FONTS
	
	// Loads a font from a prebaked .fnt and .png file
	// that share name.
	//
	// The file types should be ommited in the path.
	extern font load_font(std::string path);

	// Renders a pice of text with the specified font to the screen.
	extern void draw_text(std::string text, float size, font& f, float x, float y);

	// Gets the length of the text in the coordinate space with the specified
	// size.
	extern float get_length_of_text(std::string text, float size, font& f);

	// GENERAL RENDERING
	

	// The global and standardlyused camera.
	extern camera cam;

	// Sends in the camera matrix.
	extern void use_projection(camera c);


	// Initalizes the graphics, by registering some basic
	// meshes and initalizeing the shaders on the graphics card.
	//
	// This is called by the other init calls in the engine, and
	// should not be called. Since it probably won't do anything
	// except add some bloat to the graphcis cards memory.
	extern void init_graphics();

	// Draws a rectangle in a previousely specified color.
	extern void draw_quad(float x, float y, float w, float h);
}
