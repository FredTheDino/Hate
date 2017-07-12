// 
// This is a collection of physics constructs,
// more specifically, there are bodies, collisions
// and worlds.
//
// Bodies is anything in the world of physics, it
// is probably something that can be collided with.
// They can be static or dynamic, which means they 
// move or don't move when forces are applied to them.
//
// A world is a collection of bodies that all can 
// interact with eachother.
//
// A collision is what happens when two bodies collide.
// This holds important data and triggers a "on_collision"
// on the affected bodies.
//
#pragma once
#include "matrix.h"
#include <vector>

namespace hate {
	struct Collision;
	struct Body;

	// This is a placeholder function for the bodies on trigger.
	extern void __dummy_collision__(Collision* c);

	struct Collision {
		Body* a;
		Body* b;

		Vec2 normal;
	};

	struct Body {
		Body(float w = 1.0f, float h = 1.0f) {
			dimension.x = w;
			dimension.y = h;
		}

		float mass      = 1.0f;
		float inv_mass  = 1.0f;
		bool is_static  = true;
		bool is_trigger = false;
		
		Vec2 acceleration;
		Vec2 velocity;
		Vec2 position;

		Vec2 dimension;

		void (*on_collision)(Collision*) = __dummy_collision__;
	};

	struct World {
		std::vector<Body*> bodies;
		Vec2 gravity = Vec2(0, 1);
	};

	// Adds a body to its world.
	extern void add(World& world, Body* body);

	// Removes a body from the world.
	extern bool remove(World& world, Body* body);

	// Updates a world.
	extern void update(World& world, float delta);

	// Draws all bodies in the world, for debug purpouses.
	extern void debug_draw(World& world);
}
