#include "level.h"
#include "misc.h"
#include "graphics.h"
#include <sstream>

namespace hate {

	void register_entity_type(entity_type const& type) {
		// Makes a safe working copy.
		std::string name = type.type_name;
		entity_types[type.type_name] = type;
	}

	entity deserialize_base_entity(serialized_entity const& data) {
		entity e;

		e.type = data[0];
		e.name = data[1];

		e.t.position.x = std::stof(data[2]);
		e.t.position.y = std::stof(data[3]);

		e.t.scale.x = std::stof(data[4]);
		e.t.scale.y = std::stof(data[5]);

		e.t.rotation = std::stof(data[6]);

		e.layer = std::stof(data[7]);

		e.update = entity_types[e.type].update;
		e.draw = entity_types[e.type].draw;

		return e;
	}

	entity deserialize_entity(std::string serialized_data) {
		serialized_entity data = split(serialized_data);
		if (data[0] == "base") {
			return deserialize_base_entity(data);
		} else {
			return entity_types[data[0]].deserialize(data);
		}
	}

	void load_level(std::string path, entity_system* em) {
		// TODO
		return;
	}

	void save_level(std::string path, entity_system* em) {
		// TODO
		return;
	}

	// BASE ENTITY STUFF.
	
	void delete_base(entity* e) {}

	entity deserialize_base(serialized_entity const& data) {
		return deserialize_base_entity(data);
	}

	std::string serialize_base(entity* e) {
		std::stringstream ss;
		ss << e->type;
		ss << e->name;

		ss << e->t.position.x;
		ss << e->t.position.y;

		ss << e->t.scale.y;
		ss << e->t.scale.y;

		ss << e->t.rotation;

		ss << e->layer;

		return ss.str();
	}

	void update_base(entity* e, float delta) {}

	void draw_base(entity* e) {
		draw_quad(e->t.position.x, e->t.position.y, 1.0f, 1.0f);
	}

	// Initalizes the system.

	void initalize_entity_types() {
		entity_type type;
		type.type_name = "base";
		type.delete_entity = &delete_base;

		type.serialize = &serialize_base;
		type.deserialize = &deserialize_base;

		type.draw = &draw_base;
		type.update = &update_base;

		register_entity_type(type);
	}
}
