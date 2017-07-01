// 
// A system holds entity pointers, which
// all know how to be drawn and updated.
// The system then updates them and keeps 
// track of the entities, making sure the
// IDs are valid.
//
// Entities can be added and flagged for
// removal.
//
#pragma once

#include <vector>

#define ID_INCREMENT 0x00010000
#define ID_MASK      0x0000FFFF
#define ID_UNIQUE    0xEFFF0000
#define INVALID_ID   0xFFFFFFFF

namespace hate {
    // This is the base entity, everything else
    // has to implement a draw and an update.
    struct Entity {
        unsigned int id = INVALID_ID; 

        virtual void update(float delta) {};
        virtual void draw() {};
    };

    struct EntityIndex {
        unsigned int id = INVALID_ID; // -1 is an invalid id.
        unsigned int next_free = INVALID_ID; // Points to the next free spot.
    };

    struct System {
        // Converts an index into 
        std::vector<EntityIndex> indicies;
        std::vector<Entity*> entities;

        unsigned int next_free = INVALID_ID;
    };

    // Reserves this many entityes space for the system.
    extern void reserve(System& system, unsigned int min_size);

    // Updates all entities in the system.
    extern void update(System& system, float delta);

    // Draws all entities in the system.
    extern void draw(System& system);

    // Adds an entity to the system for updating and drawing.
    extern unsigned int add(System& system, Entity* entity);
    // Removes the entity with the ID from the system.
    extern bool remove(System& system, unsigned int id);

    // Checks if the system has an entity on that id.
    extern inline bool has(System& system, unsigned int id);
    // Returns an entity for that id, null otherwise.
    extern Entity* get(System& system, unsigned int id);
}