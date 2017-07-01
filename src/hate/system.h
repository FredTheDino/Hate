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

#define ID_INCREMENT 0x10000
#define ID_MASK 0xFFFF

namespace hate {
    // This is the base entity, everything else
    // has to implement a draw and an update.
    struct Entity {
        unsigned int id = -1; // -1 is an invalid id.

        virtual void update(float delta) = 0;
        virtual void draw() = 0;
    };

    struct EntityIndex {
        unsigned int id = -1; // -1 is an invalid id.
        unsigned int next_free = -1; // Points to the next free spot.
    };

    struct System {
        // Converts an index into 
        std::vector<EntityIndex> indicies;
        std::vector<Entity*> entities;

        unsigned int next_free = -1;
    };
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