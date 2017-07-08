#include "gamestate.h"
#include <stdio.h>

namespace hate {
	// Default functions
	void __default__ () {}
	void __default_update__ (float delta) {}

	void change_state(GameStateManager& gsm, GameState next_state) {
		gsm.change = true;
		gsm.next = next_state;
	}

	void update_state(GameStateManager& gsm, float delta) {
		// The standard loop.
		gsm.current.update(delta);
		gsm.current.draw();

		// If we need to change state, do that.
		if (gsm.change) {
			gsm.change = false;
			gsm.current.unload();
			gsm.current = gsm.next;
			gsm.current.load();
		}
	}
}
