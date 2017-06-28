//
// An entity is something that exists in the game world.
// But this engine doesn't really care about entitites,
// we care about components that link to these entities.
//
// So an entity_system is just that, a base system that
// holds entities coupled to an ID. If an entity
// is alive is implicit and 
//
#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include "math.h"
#include "behaviour.h"

#define MIN_SYSTSEM_SIZE 512
// The short part of an int is the index.
#define INDEX_MASK 0xFFFF
// The other bits of it are used to generate
// a unique ID. This way 
#define NEW_OBJECT_ADD 0x10000

namespace hate {
    // An entity is more of a lose
    // connection between components.
    struct Index {
        // The id of the entity, almost garanteed unique, unless
        // you plan on adding more than 4294967296 entities,
        // then it will slow down a bit.
        unsigned int id;
        unsigned short index;
        // The next free index if this is cleared.
        unsigned short next_free_id = -1;
    };

    // A way to keep track of entities and updates them in bulk.
    template <typename Object>
    struct System {
        // Sets the default size of relevent objects.
		System(int min_size = MIN_SYSTSEM_SIZE) {
            // This is a nice size that should fit
            // into the cache of any modern computer.
            indicies.resize(min_size);
            // Setup the indicies.
            for (int i = 0; i < indicies.size(); i++) {
                indicies[i].id = i;
                indicies[i].next_free_id = i + 1;
            }

            next_add_id = 0;
            num_entries = 0;
            next_remove_id = -1; // Max value

            objects.resize(min_size);
        }
    
        // An ID to an object.
        std::vector<Index> indicies;
        // A list of objects.
        std::vector<Object> objects; // This is where they actually live.
        // These ones are free to be changed, 2
        unsigned short next_remove_id;
        unsigned short next_add_id;
        unsigned int num_entries;
    };

    // Checks if the object is registered.
    template <typename Object>
    extern bool has(System<Object>& s, unsigned int id);

    // Adds an object to the world and returns an ID to it that can be used to reffer to it.
    //
    // The name is implicit.
    template <typename Object>
    extern unsigned int add(System<Object>& s, Object const& o);

    // Gets the object that is associated with the ID.
    template <typename Object>
    extern Object* lookup(System<Object>& s, unsigned int id);
    
    // Removes the object.
    template <typename Object>
    extern void remove(System<Object>& s, unsigned int id);

    // Clears out the system.
    template <typename Object>
    extern void clear_system(System<Object>& s);
}
