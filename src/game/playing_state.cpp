#include "states.h"
#include <stdio.h>
#include <vector>

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

	Body b(1, 1);

	World world;

	void playing_load() {
		b.position.y = 1.5;
		player.b.is_static = false;

		add(world, &b);
		add(world, &player.b);
	}

	void playing_unload() {

	}

	void playing_update(float delta) {
		// Updates the "physics engine"

		update(world, delta);

		player.grounded = false;
		if (player.b.velocity.y == 0) {
			player.grounded = true;
		}

		if (player.grounded && is_pressed("up")) {
			player.b.velocity.y = -3.0f;
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
