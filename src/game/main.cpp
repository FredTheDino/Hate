#include "core.h"
#include "input.h"
#include "graphics.h"
#include "level.h"

using namespace hate;

struct player_data {
	vec2 vel;
	vec2 acc;
};

void delete_player(entity* e) {
	delete (player_data*) e->data;
}

std::string serialize_player(entity* e) {
	return entity_types["base"].serialize(e);
}

entity deserialize_player(serialized_entity const & s) {
	entity e = entity_types["base"].deserialize(s);
	e.data = new player_data;

	return e;
}

float speed = 50.0f;

void update_player(entity* e, float delta) {
	vec2 direction;

	if (is_down("left")) {
		direction.x -= 1.0f;
	}

	if (is_down("right")) {
		direction.x += 1.0f;
	}
	
	if (is_down("down")) {
		direction.y += 1.0f;
	}

	if (is_down("up")) {
		direction.y -= 1.0f;
	}

	direction = direction.normalize();

	player_data* v = ((player_data*) e->data);

	v->acc = v->acc + (direction * delta * speed);
	v->acc = v->acc * 0.75f;
	v->vel = v->vel + (v->acc * delta);
	e->t.position = e->t.position + v->vel * delta;
}

void draw_player(entity* e) {
	draw_quad(e->t.position.x, e->t.position.y, 1, 1);
}

int main(int c, char** v) {
	hate::init_hate();

	entity_type player;
	player.type_name = "player";

	player.delete_entity = delete_player;

	player.serialize = serialize_player;
	player.deserialize = deserialize_player;

	player.draw = draw_player;
	player.update = update_player;

	register_entity_type(player);

	entity p = deserialize_entity("player player 0 0 1 1 0 0");
	add_entity(em, p);

	hate::run_hate();

	return 0;
}
