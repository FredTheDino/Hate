#pragma once
#include <core.h>
#include <input.h>
#include <graphics.h>
#include <level.h>
#include <math.h>
#include <clock.h>

using namespace hate;

extern float speed;
extern float max_speed;

struct player_data {
	float vel = 0.0f;
};

extern void delete_player(entity* e);

extern std::string serialize_player(entity* e);

extern int sign(float f);

extern void update_player(entity* e, float delta);


extern void draw_player(entity* e);

extern void register_player_type();
