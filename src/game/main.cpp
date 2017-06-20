#include <core.h>
#include "player.h"

using namespace hate;

int main(int c, char** v) {
	hate::init_hate();

	cam.zoom = 5.0f;

	register_player_type();

	entity p = deserialize_entity("player player 0 0 1 1 0 0");
	add_entity(em, p);

	hate::run_hate();

	return 0;
}
