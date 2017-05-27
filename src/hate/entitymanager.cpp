#include "entitymanager.h"

namespace hate {

	EntityManager::EntityManager() {}

	// Checks if a cirtain ID is marked as free.
	bool isFree(std::stack<unsigned int> empty, unsigned int id) {
		unsigned int i;
		while (!empty.empty()) {
			i = empty.top();
			if (i == id)
				return true;
			empty.pop();
		}
		return false;
	}

	EntityManager::~EntityManager() {
		for (unsigned int id = 0; id < entities.size(); id++) {
			if (!isFree(empty, id)) {
				delete entities[id];
			}
		}
	}
	
	void EntityManager::init() {
		// Am I supposed to do something here?
	}

	unsigned int EntityManager::add(Entity* e, std::string name) {
		unsigned int id = add(e);
		lookup[name] = id;
		return id;
	}

	unsigned int EntityManager::add(Entity* e) {
		unsigned int id;
		if (empty.size() == 0) {
			// We have to expand the array.
			id = entities.size();
			entities.push_back(e);
		} else {
			// Woo! We didn't have to allocate.
			id = empty.top();
			empty.pop();
			entities[id] = e;
		}	
		return id;
	}

	Entity* EntityManager::get(unsigned int id) {
		return entities[id];
	}

	Entity* EntityManager::get(std::string name) {
		auto it = lookup.find(name);
		if (it != lookup.end()) {
			return entities[it->second];
		}
		return nullptr;
	}

	Entity* EntityManager::get(const char* name) {
		return get(std::string(name));
	}

	void EntityManager::update(float delta) {
		for (int i = 0; i < entities.size(); i++) {
			entities[i]->update(delta);
			if (entities[i]->trash) {
				trash.push_back(i);
			}
		}
	}

	void EntityManager::draw() {
		for (auto e : entities) {
			e->draw();
		}
	}

	void EntityManager::emptyTrash() {
		// We delete backwards so we don't ruin the rest of the list.
		for (int i = trash.size(); 0 <= i ; i--) {
			unsigned int id = trash[i];
			empty.push(id);
			Entity* e = entities[id];

			std::string name = e->name;
			if (!name.empty()) {
				// Aha, you have a name!
				lookup.erase(name);
			}

			delete e;
		}
		// Empty it.
		trash.clear();
	}
}
