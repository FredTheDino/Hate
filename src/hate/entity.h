#pragma once
#include <unordered_map>
#include "drawable.h"
#include "transform.h"

#define _ENTITY_
namespace hate {

	/**
	 * The entity typename holds components witch are
	 * updated by the entity manager. 
	 */
	class Entity {
		public:
			// Creates a new entity.
			Entity(std::string name = "");

			// Destroys an entity and all its components.
			~Entity();

			// A name that can be given during creation.
			std::string name = "";

			// If the entity should be trashed.
			bool trash = false;

			// A transform that every entity has.
			Transform transform;
			// A drawable, that allows you to draw this.
			Drawable drawable;

			// Updates everything that is needed to be
			// updated.
			void update(float delta);

			// What you should do when you want to draw.
			void draw();

		private:
	};
}
