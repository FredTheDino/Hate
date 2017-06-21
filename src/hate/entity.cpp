#include "entity.h"
#include <assert.h>

namespace hate {

	unsigned int add_entity(entity_system& em, entity const& e) {
		unsigned int id = 0;

		

		return id;
	}
	
	void change_layer(entity_system& em, unsigned int id, int layer) {
		change_layer(em, &em.by_id[id], layer);
	}

	void change_layer(entity_system& em, entity* e_ptr, int layer) {
		int current_layer = e_ptr->layer;
		auto e_pos = em.by_layer.find(current_layer);

		while (e_pos->second != e_ptr) {
			if (e_pos == em.by_layer.end() || e_pos->first != current_layer) {
				// It's not here...
#ifdef DEBUG
				printf("Warning: You tried to switch the layer on an entity that doesn't exist.\n");
#endif
				return;
			}
			e_pos++;
		}
	
		// Remove it.
		em.by_layer.erase(e_pos);

		// Place it in the new place.
		em.by_layer.insert(std::make_pair(layer, e_ptr));
		e_ptr->layer = layer;
	}

	// Deletes from everything but by_layer.
	void delete_entity_from_system(entity_system& em, entity* e_ptr) {
		if (em.by_name[e_ptr->name] == e_ptr) {
			// We're the ones stored on this name
			// so delete us!
			em.by_name.erase(e_ptr->name);
		}

		// I don't want to delete something if it isn't there.
		if (&em.by_id[e_ptr->id] == e_ptr) {
			em.by_id.erase(e_ptr->id);
		}
	}

	void update(entity_system& em, float delta) {
		auto it = em.by_layer.begin();

		entity* current;
		while (it != em.by_layer.end()) {
			current = it->second;
			// If it's trash, it gotta go!
			if (current->trash) {
				delete_entity_from_system(em, current);
				it = em.by_layer.erase(it);
				continue;
			}
			
			current->update(current, delta);

			// If it's state changed, it gets added.
			if (current->trash) {
				delete_entity_from_system(em, current);
				it = em.by_layer.erase(it);
				continue;
			}
			it++;
		}
	}

	void draw(entity_system& em) {
		auto it = em.by_layer.begin();

		entity* current;
		while (it != em.by_layer.end()) {
			current = it->second;
			current->draw(current);
			it++;
		}
	}
	
	void clear_entity_system(entity_system& em) {
		em.by_layer.clear();
		em.by_name.clear();
		em.by_id.clear();
	}
}
