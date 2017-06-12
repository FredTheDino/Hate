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
	// Woo C++ BS.
	struct entity;

	// Something to default the update function to.
	extern void dummy_update(entity* e, float delta);
	
	// Something to default the draw function to.
	extern void dummy_draw(entity* e);

	// This is your one stop shop for "game objects".
	//
	// NOTE: The NAME and LAYER properties should
	// ONLY BE READ. They don't actually update
	// in the entity_system, but maybe they should?
	struct entity {
		// This decides if it should be destroyed efter the cycle.
		bool trash = false;
		// The id of the entity, almost garanteed unique, unless
		// you plan on adding more than 4294967296 entities,
		// then it will slow down a bit.
		unsigned int id;
		// A name that can be used for identification.
		std::string name = "Entity";
		// This decides what kind of entity this is.
		std::string type = "base";
		// A transform for position, scale and rotation.
		transform t;
		// A layer to be drawn on.
		int layer = 0;

		// A bunch of extra data.
		void* data = nullptr;

		// Maybe not have these here...
		// How this should be updated.
		void (*update)(entity*, float) = &dummy_update;
		// How this should be drawn.
		void (*draw)(entity*) = &dummy_draw;

		// A behaviour.
		behaviour b;
	};


	// A way to keep track of entities and updates them in bulk.
	struct entity_system {
		// @Robustness: Memory fragmentation is going to be
		// a real problem here. Should I implement some kind
		// of data structure for keeping track of holes.
		//
		// @Note: Filling the list compleatly is roughly 120GB
		// of ram. I think it's safe to say other things will
		// go wrong before we see the problem with memory 
		// fragmentation, that the multimap should handle
		// for us.

		// The way they are updated.
		// A layer mapped to a list of entites which are to be updated.
		std::multimap<int, entity*> by_layer;
		// In a named list, will only store the latest entity with that name.
		// This saves space on stuff you don't want to access.
		// @Memeory: We can store the ID, which is a u32 instead of
		// a 64bit pointer on 64 bit systems.
		std::unordered_map<std::string, entity*> by_name;
		// An ID to an entity.
		std::map<unsigned int, entity> by_id; // This is where they actually live.
	};

	// Adds an entity to the world and returns an ID to it that can be used to reffer to it.
	extern unsigned int add_entity(entity_system& em, entity const& e); 
	
	// Changes the layer of the entity in the entity system.
	extern void change_layer(entity_system& em, unsigned int id, int layer);
	extern void change_layer(entity_system& em, entity* e_ptr, int layer);

	// Updates this entity system.
	extern void update(entity_system& em, float delta);

	// Draws all the entities.
	extern void draw(entity_system& em);

	// @Thoughs: I don't need this function, I can just use .by_id[id] instead. 
	// This would only be to claeify code and I don't want to add that
	// at this point.
	//
	// Returns the entity associated with this id.
	// @Unity: Should I really return this by refference? It's not
	// done anywhere else...
	// extern entity& get_entity(entity_system& em, unsigned int id);

	// Clears out the entity_system.
	extern void clear_entity_system(entity_system& em);
}
