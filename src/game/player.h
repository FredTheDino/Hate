#pragma once
#include <core.h>
#include <input.h>
#include <graphics.h>
#include <level.h>
#include <math.h>

using namespace hate;

float speed = 5000.0f;
float max_speed = 0.5f;

struct player_data {
	float vel = 0.0f;
};

void delete_player(entity* e) {
	printf("Deleteing stuff!\n");
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

int sign(float f) {
	if (f < 0) {
		return -1;
	}
	return 1;
}

void update_player(entity* e, float delta) {
	player_data* p = ((player_data*) e->data);

	if (is_down("left")) {
		e->t.rotation -= M_PI / 5 * delta;
	}

	if (is_down("right")) {
		e->t.rotation += M_PI / 5 * delta;
	}
	
	if (is_down("down")) {
		p->vel -= 1 * delta;
	}

	if (is_down("up")) {
		p->vel += 1 * delta;
	}
	
	if (abs(p->vel) > max_speed) {
		p->vel = sign(p->vel) * max_speed;
	}

	e->t.position = e->t.position + rotate(vec2(0, -1), e->t.rotation) * p->vel * delta;
}

void draw_player(entity* e) {
	mat4 t = gen_transform(e->t);
	print_mat("trans", t);
	draw_quad(t);
}

inline void register_player_type() {
	entity_type player;
	player.type_name = "player";

	player.delete_entity = delete_player;

	player.serialize = serialize_player;
	player.deserialize = deserialize_player;

	player.draw = draw_player;
	player.update = update_player;

	register_entity_type(player);
}
