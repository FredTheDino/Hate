#include "system.h"
#include <assert.h>

namespace hate {

	template <typename object>
	unsigned int add(system<object>& s, object const& o) {
		// Take a free index, and move the next_add_id pointer to a new one.
		Index& i = s.indicies[s.next_add_id];
		s.next_add_id = i.next;

		// We can later pack this array
		// when it gets fragmented.
		i.id += NEW_OBJECT_ADD;
		i.index = s.num_entries;
		s.num_objects++;

		// We might make this into another
		// branch which packs the array.
		assert(i.index < objects.size());

		// Copy over the id.
		s.objects[i.index] = o;
		s.objects[i.index].id = i.id;

		return i.id;
	}
	
	inline bool has(system& s, unsigned int id) {
		Index& i = s.indicies[id & INDEX_MASK];
		return i.id == id && i.index != -1;
	}

	template <typename object>
	inline object* lookup(systme<object>& s, unsigned int id) {
		return &s.objects[s.indicies[id & INDEX_MASK].index];
	}

	template <typename object>
	void remove(system<object>& s, unsigned int id) {
		// Make some refferences.
		Index& i = s.indicies[id & INDEX_MASK];
		object& o = s.object[i.index];
		
		// Replace the object by moving it in
		// the array to a better position.
		s.num_entries--;
		o = _objects[s.num_entries];
		s.indices[o.id & INDEX_MASK].index = in.index;

		// Delete the old index.
		i.index = -1; // Max it out.
		s.indices[s.next_removed_id].next = id & INDEX_MASK;
		s.next_removed_id = id & INDEX_MASK;
	}

	void clear_system(system& s) {
		for (int i = 0; i < s.indicies.size(); i++) {
			s.indicies[i].index = -1;
		}
	}
}
