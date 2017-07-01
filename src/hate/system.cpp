#include "system.h"
#include <assert.h>

namespace hate {
    void update(System& system, float delta) {
        for (auto e : system.entities) {
            if (e->id == -1) continue;
            e->update(delta);
        }
    }

    void draw(System& system) {
        for (auto e : system.entities) {
            if (e->id == -1) continue;
            e->draw();
        }
    }

    unsigned int add(System& system, Entity* entity) {
        EntityIndex index;
        if (system.next_free == -1) {
            // There isn't a free spot.
            index.id = system.entities.size();
            entity->id = index.id;

            system.entities.push_back(entity);
            system.indicies.push_back(index);
        } else {
            // There is a free spot!
            // Get a new free spot if there is one.
            index = system.indicies[system.next_free];
            system.next_free = index.next_free;

            // Increment the index to prevent collisions.
            index.id += ID_INCREMENT;
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
        system.next_free = index.id;
        // Clear the entity id.
        system.entities[index.id & ID_MASK]->id = -1;
            
        return true;
    }

    bool has(System& system, unsigned int id) {
        if (id & ID_MASK > system.indicies.size()) return false;

        return 
            system.indicies[id & ID_MASK].id == id && 
            system.entities[id & ID_MASK]->id != -1;
    }

    Entity* get(System& system, unsigned int id) {
        if (has(system, id)) {
            return system.entities[id & ID_MASK];
        }
        return nullptr;
    }
}
