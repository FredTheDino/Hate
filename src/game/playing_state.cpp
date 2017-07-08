#include "states.h"
#include <stdio.h>

#include <input.h>
#include <graphics.h>

namespace ps {
	using namespace hate;

	Transform player;

	void playing_load() {
		draw_color(Vec4(0.75, 0.22, 0.80, 1.0));
	}

	void playing_unload() {

	}

	void playing_update(float delta) {
		if (is_down("down")) {
			player.position.y += delta;
		}

		if (is_down("up")) {
			player.position.y -= delta;
		}
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
