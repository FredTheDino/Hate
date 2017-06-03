//
// The graphics file is for drawing things to the screen.
// It supports drawing squares, with and without textures
// by default.
//
#pragma once

namespace hate {
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
