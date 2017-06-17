// 
// A level is a file on the harddrive
// that can be converted to a list of
// entities.
//
// The base format:
// (Space seperated.)
//
// base:
// entity_type_name name x y s_x s_y r layer
#pragma once
#include "entity.h"
#include <string>
#include <vector>
typedef std::vector<std::string> serialized_entity;


namespace hate {
#ifndef _ENTITY_TYPE_
#define _ENTITY_TYPE_
	// A type of type.
	struct entity_type {
		//
		// Meta data
		//
			
		// The name this type goes by.
		std::string type_name; 
		// How to delete the entity type.
		void (*delete_entity)(entity*);

		//
		// Serialization
		//
		
		// How to serialize this entity type.
		std::string (*serialize)(entity*);
		// How to deserialze this entity.
		entity (*deserialize)(serialized_entity const&);
		
		//
		// GAMEPLAY
		//

		// How to draw this entity.
		void (*draw)(entity*);
		// How to update this type of entity.
		void (*update)(entity*, float);
	};
#endif

	// The list of all registerd entity types.
	extern std::unordered_map<std::string, entity_type> entity_types;

	// Sets up everything by registering some base types.
	extern void initalize_entity_types();

	// Adds a type of entity that can be serielized,
	// unserialized, updated and draw, says what
	// the extra data is and how it is used.
	void register_entity_type(entity_type const& type);

	// Turns a string into an entity, as if by magic.
	entity deserialize_entity(std::string serialized_data);

	// Turns an entity into text.
	std::string serialize_entity(entity* e);
	
	// Loads a level and gives you the corresponding entity system.
	void load_level(std::string path, entity_system* em);

	// Saves the level to that specified file.
	void save_level(std::string path, entity_system* em);
}
