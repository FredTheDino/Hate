//
// An entity is something that exists in the 
// game world. It can be a car or a tank,
// or even a player. But it is in the begining
// just a data type.
//
#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include "math.h"
#include "behaviour.h"

namespace hate {
	// An entity is more of a lose
	// connection between components.
	struct entity {
		// A transform is so generic 
		union {
			// This is a copy of the transform
			// struct, it's just for ease of
			// access.
			struct {
				vec2 position;
				vec2 scale;
				float rotation;
			};
			transform t;
		};
		// This decides if it should be destroyed efter the cycle.
		bool trash = false;
		// The id of the entity, almost garanteed unique, unless
		// you plan on adding more than 4294967296 entities,
		// then it will slow down a bit.
		unsigned short id;
		// The next free index if this is cleared.
		unsigned short next_free_id = -1;
		// A name that can be used for identification.
		std::string name = "Entity";
	};


	// A way to keep track of entities and updates them in bulk.
	struct entity_system {
		// Will only store the ID of the latest ID.
		std::unordered_map<std::string, unsigned int> by_name;
		// An ID to an entity.
		std::vector<entity> by_id; // This is where they actually live.
		// These ones are free to be changed, 2
		unsigned int free_id = -1;
	};

	// Adds an entity to the world and returns an ID to it that can be used to reffer to it.
	extern unsigned int add_entity(entity_system& em, entity const& e); 

	// Gets the entity that is associated with the ID.
	extern entity* lookup(entity_system& em, unsigned int id);
	
	// Gets the entity that is associated with the name.
	extern entity* lookup(entity_system& em, std::string name);
	
	// Empties the trash of the entity system.
	extern void empty_trash(entity_system& em);

	// Clears out the entity_system.
	extern void clear_entity_system(entity_system& em);
}
