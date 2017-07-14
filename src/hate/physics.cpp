#include "physics.h"
#include "graphics.h"

namespace hate {

	// A helper function, I don't know why this isn't in the STL
	int sign(float f) {
		if (f < 0) {
			return -1;
		}
		return 1;
	}

	inline float abs(float f) {
		return fabs(f);
	}
	
	// THe dummy...
	void __dummy_collision__(Collision* c) {}

	// Adds a body to its world.
	extern void add(World& world, Body* body) {
		int size = world.bodies.size();
		for (int i = 0; i < size; i++) {
			Body* b = world.bodies[i];
			if (b == nullptr) {
				b = body;
				return;
			}
		}
		world.bodies.push_back(body);
	}

	// Removes a body from the world.
	extern bool remove(World& world, Body* body) {
		int size = world.bodies.size();
		for (int i = 0; i < size; i++) {
			Body* b = world.bodies[i];
			if (b == body) {
				b = nullptr;
				return true;
			}
		}
		return false;
	}

	// Updates a world.
	extern void update(World& world, float delta) {
		for (auto b_ptr : world.bodies) {
			Body& b = *b_ptr;
			if (b.is_static || b.is_trigger) continue;
			// Might need to change this to a better numeric integration.
			b.velocity = b.velocity + world.gravity * delta;
			b.position = b.position + b.velocity    * delta;
		}

		for (int i = 0; i < world.bodies.size(); i++) for (int j = 0; j < i; j++) {
			// Collision Detection //
			Body& a = *world.bodies[i];
			Body& b = *world.bodies[j];

			if (&a == &b) continue;
			if (a.is_static && b.is_static) continue;
			if (dot(a.velocity, b.velocity) < 0) continue;
			
			Vec2 d_pos = a.position - b.position;
			Vec2 sat = Vec2(
					abs(d_pos.x) - (a.dimension.x + b.dimension.x),
					abs(d_pos.y) - (a.dimension.y + b.dimension.y));

			if (sat.x > 0 || sat.y > 0) continue;
			// Now we know we have a collision.
			
			// Collision Handleing //
			// Find the axis with the smalest position difference.
			Collision c;
			printf("X: %f, Y: %f\n", sat.x, sat.y);
			if (sat.x > sat.y) {
				// X Axis
				c.normal.x = sign(d_pos.x);
			} else {
				// Y Axis
				c.normal.y = sign(d_pos.y);
			}

			// I don't know if this is faster, but it looks cool.
			c.depth = c.normal.x * sat.x + c.normal.y * sat.y;

			// The A-Body is allways the collision itself.
			// and the normal points from A to B.
			c.a = &a;
			c.b = &b;
			a.on_collision(&c);
			// Why they're swaped here.
			c.b = &a;
			c.a = &b;
			c.normal = -c.normal;
			b.on_collision(&c);

			// Flip it back.
			c.normal = -c.normal;

			// If either of the bodies are a trigger, there is no collision response.
			if (a.is_trigger || b.is_trigger) continue;


			// Note: The normal is pointing from B to A.
			if (a.is_static) {
				// A is static
				b.position = b.position - c.normal * c.depth;
				b.velocity = b.velocity - c.normal * dot(c.normal, b.velocity);
			} else if (b.is_static) {
				// B is static
				a.position = a.position + c.normal * c.depth;
				a.velocity = a.velocity - c.normal * dot(c.normal, a.velocity);
			} else {
				// None is static
				c.depth *= 0.5f;

				b.position = b.position - c.normal * c.depth;
				a.position = a.position + c.normal * c.depth;

				float total_force = 
					abs(dot(c.normal, a.velocity) * a.mass) + 
					abs(dot(c.normal, b.velocity) * b.mass);
				float total_mass = a.mass + b.mass;

				a.velocity = a.velocity - c.normal * total_force * total_mass * a.inv_mass;
				b.velocity = b.velocity + c.normal * total_force * total_mass * b.inv_mass;
			}
		}
	}

	// Draws all bodies in the world, for debug purpouses.
	extern void debug_draw(World& world) {
		Vec4 color;
		for (int i = 0; i < world.bodies.size(); i++) {
			Body& b = *world.bodies[i];

			// Determenistic color selection.
			color = Vec4(sin((float) i * 2.324f) * 0.5f + 0.5f, 1.0f, cos((float) i * 1.123f) * 0.5f + 0.5f, 1.0f);
			draw_color(color);
			draw_quad(b.position.x, b.position.y, b.dimension.x * 2, b.dimension.y * 2);
		}
	}
}
