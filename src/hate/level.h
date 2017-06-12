// 
// A level is a file on the harddrive
// that can be converted to a list of
// entities.
//
#pragma once
#include "entity.h"

namespace hate {
	// A type of type.
	struct entity_type {
		// The name this type goes by.
		std::string type_name;
		// How to serialize this entity type.
		std::string (*serialize)(entity*);
		// How to deserialze this entity.
		entity (*deserialize)(std::string);
		// How to draw this entity.
		void (*draw)(entity*);
		// How to update this type of entity.
		void (*updater)(entity*, float);
	};

	// The list of all registerd entity types.
	std::unordered_map<std::string, entity_type> entity_types;

	// Adds a type of entity that can be serielized,
	// unserialized, updated and draw, says what
	// the extra data is and how it is used.
	void add_entity_type(entity_type& type);
	
	// Loads a level and gives you the corresponding entity system.
	void load_level(std::string path, entity_system* em);

	// Saves the level to that specified file.
	void save_level(std::string path, entity_system* em);
}
