#include "states.h"
#include <stdio.h>

#include <input.h>
#include <graphics.h>

namespace ps {
	using namespace hate;

	struct Player {
		union {
			Transform t;
			struct {
				Vec2 position;
				Vec2 scale;
				float rotation;
			};
		};

		Vec2 vel;

		bool grounded = false;

	} player;

	float gravity = 6.0f;

	void playing_load() {
		draw_color(Vec4(0.75, 0.22, 0.80, 1.0));
	}

	void playing_unload() {

	}

	void playing_update(float delta) {

		player.vel.y += gravity * delta;
		player.grounded = false;
		if (player.position.y >= 0.0f) {
			player.position.y = 0.0f;
			player.vel.y = 0.0f;
			player.grounded = true;
		}

		if (player.grounded && is_pressed("up")) {
			player.vel.y = -3.0f;
		}

		player.position.y += player.vel.y * delta;
	}

	void playing_draw() {
		draw_quad(gen_transform(player));;
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
