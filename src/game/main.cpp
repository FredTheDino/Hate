#include <core.h>
#include <graphics.h>
#include <gamestate.h>
#include "states.h"

using namespace hate;

float t = 0.0f;


int main(int c, char** v) {
	hate::init_hate();

	cam.zoom = 2.5f;
	hate::change_state(hate::gsm, playing_state());

	hate::run_hate();

	return 0;
}
