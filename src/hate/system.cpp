#include "system.h"
#include <assert.h>
#include <stdio.h>

namespace hate {
    void update(System& system, float delta) {
        for (auto e : system.entities) {
            if (e->id == INVALID_ID) continue;
            e->update(delta);
        }
    }

    void draw(System& system) {
        for (auto e : system.entities) {
            if (e->id == INVALID_ID) continue;
            e->draw();
        }
    }

    void reserve(System& system, unsigned int min_size) {
        system.indicies.reserve(min_size);
        system.entities.reserve(min_size);
    }

    unsigned int add(System& system, Entity* entity) {
        EntityIndex index;
		printf("Sys next: %u, Iv id: %u\n", system.next_free, INVALID_ID);
		printf("Wooo!\n");
        if (system.next_free = (INVALID_ID)) {
            // There isn't a free spot.
            index.id = system.entities.size();
            entity->id = index.id;

            system.entities.push_back(entity);
            system.indicies.push_back(index);
        } else {
            // There is a free spot!
            // Get a new free spot if there is one.
            index = system.indicies[system.next_free];
            system.next_free = index.next_free & ID_MASK;

            // Increment the index to prevent collisions.
            // And stack overflows
			if ((index.id & ID_UNIQUE) == ID_UNIQUE) {
				index.id = index.id & ID_MASK;
            } else {
                index.id += ID_INCREMENT;
            }
            entity->id = index.id;            
            
            system.indicies[index.id & ID_MASK] = index;
            system.entities[index.id & ID_MASK] = entity;
        }

        return index.id;
    }

    bool remove(System& system, unsigned int id) {
        if (!has(system, id)) {
            return false;
        }
           
        EntityIndex& index = system.indicies[id & ID_MASK];
        index.next_free = system.next_free;
        system.next_free = index.id & ID_MASK;
        // Clear the entity id.
        system.entities[index.id & ID_MASK]->id = INVALID_ID;
            
        return true;
    }

    bool has(System& system, unsigned int id) {
        if (id & ID_MASK > system.indicies.size()) return false;

        return 
            system.indicies[id & ID_MASK].id == id && 
            system.entities[id & ID_MASK]->id != INVALID_ID;
    }

    Entity* get(System& system, unsigned int id) {
        if (has(system, id)) {
            return system.entities[id & ID_MASK];
        }
        return nullptr;
    }
}
