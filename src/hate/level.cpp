#include "level.h"
#include "misc.h"
#include "graphics.h"
#include "loader.h"
#include <fstream>
#include <sstream>


namespace hate {
	std::unordered_map<std::string, entity_type> entity_types;

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
		return entity_types[data[0]].deserialize(data);
	}

	void load_level(std::string path, entity_system* em) {
		std::string real_path = get_real_path(path);
		std::ifstream file(real_path.c_str());

		std::string line;
		while(std::getline(file, line)) {
			// If it starts with a hash, it's a comment.
			if (line[0] == '#') continue;
			add_entity(*em, deserialize_entity(line));
		}

		return;
	}

	void save_level(std::string path, entity_system* em) {
		std::string real_path = get_real_path(path);
		std::ofstream file(real_path.c_str());

		for (auto& e : em->by_id) {
			file << entity_types[e.second.type].serialize(&e.second);
			file << "\n";
		}

		file.close();
	}

	// BASE ENTITY STUFF.
	
	void delete_base(entity* e) {}

	std::string serialize_base(entity* e) {
		std::stringstream ss;
		ss << e->type;
		ss << " ";
		ss << e->name;
		ss << " ";

		ss << e->t.position.x;
		ss << " ";
		ss << e->t.position.y;
		ss << " ";

		ss << e->t.scale.y;
		ss << " ";
		ss << e->t.scale.y;
		ss << " ";

		ss << e->t.rotation;
		ss << " ";

		ss << e->layer;
		ss << " ";

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
		type.deserialize = &deserialize_base_entity;

		type.draw = &draw_base;
		type.update = &update_base;

		register_entity_type(type);
	}
}
