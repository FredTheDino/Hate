->#pragma once
#include <vector>
#include <stack>
#include <unordered_map>
#include "entity.h"

namespace hate {
	/**
	 * An entitymanager holds a reffernce
	 * to all entities ever created. This 
	 * is so that you don't have to.
	 *
	 * It is ILLEGAL to hold an entity 
	 * pointer over an update call. 
	 * This is to make sure entities 
	 * can be deleted and cleared out
	 * of the system before the next 
	 * loop without side effects.
	 */
	class EntityManager {
		public:

			EntityManager();

			~EntityManager();

			// Adds an entity and calls it a name.
			unsigned int add(Entity* e, std::string name);

			// Adds an entity
			unsigned int add(Entity* e);

			// Initalizes the manager.
			void init();

			// Called every frame.
			void update(float delta);

			// Draws all entities that want to be drawn.
			void draw();

			// Empties the trash.
			void emptyTrash();

			// Returns the pointer to the entity with the name.
			Entity* get(unsigned int id);
			Entity* get(std::string name);
			Entity* get(const char* name);
		private:
			// A list of all entities in play.
			std::vector<Entity*> entities;
			// A list of the un used places in the list.
			std::stack<unsigned int> empty;
			// A list of entities that should be deleted
			// at the end of the frame.
			std::vector<unsigned int> trash;
			// A lookup table for named entities.
			std::unordered_map<std::string, unsigned int> lookup;
	};
}
