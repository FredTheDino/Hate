// 
// A GameState is a way to handle "scenes", or simular purely 
// through code. It doesn't translate that well to a gui
// since the updateloop is the main reason for having it.
//
#pragma once

namespace hate {
	// Default functions, they're empty functions.
	extern void __default__        (void);
	extern void __default_update__ (float delta);

	// Things every gamestate should have. 
	struct GameState {
		// Called to initalize.
		void (*load)(void) = __default__;
		// Calles to deinitalize.
		void (*unload)(void) = __default__;
		// Called everyframe.
		void (*update)(float delta) = __default_update__;
		// Called to draw.
		void (*draw)(void) = __default__;
	};

	struct GameStateManager {
		// The current gamestate.
		GameState current;
		// The next gamestate to change to.
		GameState next;
		// Decides if the GameState should change.
		bool change = false; 
	};

	// Changes the state to the speccified one as soon as possible.
	extern void change_state(GameStateManager& gsm, GameState next_state);

	// Updates the gamestate and the gamestate manager.
	extern void update_state(GameStateManager& gsm, float delta);
}
