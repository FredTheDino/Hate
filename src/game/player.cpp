#include "player.h"

float max_speed = 2.5f;
float time_accelerated = 0;

void delete_player(entity* e) {
	printf("Deleteing stuff!\n");
	delete (player_data*) e->data;
}

std::string serialize_player(entity* e) {
	return entity_types["base"].serialize(e);
}

entity deserialize_player(serialized_entity const & s) {
	entity e = entity_types["base"].deserialize(s);
	e.t.scale.y = 2;
	e.data = new player_data;
	return e;
}

int sign(float f) {
	if (f < 0) {
		return -1;
	}
	return 1;
}

float abs(float a) {
	if (a < 0) {
		return -a;
	}
	return a;
}

float v(float x) {
	return 
		- 0.050 * x * x * x * x 
		+ 0.133 * x * x * x 
		- 0.100 * x * x;
}

float f(float x) {
	return sign(x) * v(abs(x)) / v(1) * max_speed; 
}

void update_player(entity* e, float delta) {
	player_data* p = ((player_data*) e->data);

	if (is_down("cam_up")) {
		cam.position.y += delta;
	}

	if (is_down("cam_down")) {
		cam.position.y -= delta;
	}
	
	if (is_down("cam_left")) {
		cam.position.x -= delta;
	}

	if (is_down("cam_right")) {
		cam.position.x += delta;
	}
	

	if (abs(time_accelerated) < delta) {
		time_accelerated = 0;
	} else {
		time_accelerated = time_accelerated - sign(time_accelerated) * delta * 0.2;
	}
	
	if (is_down("down")) {
		time_accelerated -= delta;
		time_accelerated = (-1 < time_accelerated) ? time_accelerated : -1;
	}

	if (is_down("up")) {
		time_accelerated += delta;
		time_accelerated = (1 > time_accelerated) ? time_accelerated : 1;
	}
	
	/*
	if (abs(p->vel) > max_speed) {
		p->vel = sign(p->vel) * max_speed;
	}
	*/
	p->vel = f(time_accelerated);

	if (is_down("left")) {
		e->t.rotation -= M_PI / 5 * delta * p->vel; 
	}

	if (is_down("right")) {
		e->t.rotation += M_PI / 5 * delta * p->vel;
	}

	e->t.position = e->t.position + rotate(vec2(0, -1), e->t.rotation) * p->vel * delta;
}


void draw_player(entity* e) {

	mat4 main_transform = gen_transform(e->t);

	// Not sure if I want this or not...
/*
	vec2 turret_position(0, -0.01f);
	turret_position = main_transform * turret_position;

	vec2 mouse_pos = mouse_to_world();
//	mouse_pos.y *= -1;

	float angle = atan2(turret_position.x - mouse_pos.x, 
			turret_position.y + mouse_pos.y);
	angle = angle - e->t.rotation;

	mat4 turret_tansform = translation(0 , -0.01f);
	turret_tansform = rotation(angle);
*/
	draw_color(vec4(1, 0, 1, 1));
	draw_quad(main_transform);
/*
	draw_color(vec4(1, 1, 0, 1));
	draw_quad(main_transform * turret_tansform);
*/
}

void register_player_type() {
	entity_type player;
	player.type_name = "player";

	player.delete_entity = delete_player;

	player.serialize = serialize_player;
	player.deserialize = deserialize_player;

	player.draw = draw_player;
	player.update = update_player;

	register_entity_type(player);
}
