#include "states.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include <input.h>
#include <clock.h>
#include <graphics.h>
#include <physics.h>

namespace ps {
	using namespace hate;


	struct Player {
		Body b = Body(1, 1);

		Transform t;

		bool grounded = false;

	} player;

	void player_collision(Collision* c) {
		Collision& col = *c;
		/*
		if (dot(col.normal, Vec2(0, 1)) > 0.75f) {
			player.grounded = true;
			col.a->velocity.y = 0;
		}
		*/
		printf("Normal: %f, %f\n", col.normal.x, col.normal.y);
		//col.a->position = col.b->position + col.normal * col.depth;
	}

	// All the walkable platforms.
	typedef std::vector<Body> Path;
	Path path;

	const float start =  3;
	const float end   = -3;

	void init(Path& path, World& world) {
		const int num_per_unit = 2;
		float step = (start - end) / num_per_unit;
		path.resize(10);
		for (float x = end; x < start; x += step) {
			Body b;
			//b.is_trigger = true;
			b.position.x = x;
			b.position.y = ((float) rand()) / ((float) RAND_MAX);

			path.push_back(b);

			add(world, &path[path.size() - 1]);
			break;
		}
	}

	void update(Path& path, float delta) {
		const float speed = 0.5f;
		for (Body& b : path) {
			b.position.x -= speed * delta;
			while (b.position.x < end) {
				b.position.x += start - end;
				b.position.y = ((float) rand()) / ((float) RAND_MAX);
			}
		}
	}

	World world;

	void playing_load() {
		player.b.is_static = false;
		player.b.is_trigger = false;
		player.b.on_collision = player_collision;

		cam.zoom = 5;

		world.gravity.y = 10;
		add(world, &player.b);
		init(path, world);
	}

	void playing_unload() {

	}

	void playing_update(float delta) {
		// Updates the "physics engine"
		update(path, delta);

		player.grounded = false;
		update(world, delta);
		player.b.position.x = 0;

		if (player.grounded && is_pressed("up")) {
			player.b.velocity.y = -3.0f;
		}
		
		if (is_pressed("down")) {
			player.b.position.y = -2;
			player.b.velocity.y = 0;
		}
	}

	void playing_draw() {
		debug_draw(world);
	}
}

hate::GameState playing_state() {
	hate::GameState state;

	state.load   = ps::playing_load;
	state.unload = ps::playing_unload;
	state.update = ps::playing_update;
	state.draw   = ps::playing_draw;

	return state;
}
