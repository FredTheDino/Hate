#include "entity.h"

namespace hate {

	Entity::Entity() {}

	Entity::~Entity() {}

	template <class T> T* Entity::get() {
		T target;
		auto found = components.find(target.getKey());

		if (found == components.end()) {
			return nullptr;
		}

		return (T*) found->second;
	}

	template <class T> bool Entity::add(T* component) {
		if (get<T>()) {
			components.insert(std::pair<std::string, Component*>(component->getKey(), (Component*) component));
			component->setParent(this);
			component->init();
			return true;
		}
		return false;
	}

	template <class T> void Entity::remove() {
		T* target = get<T>();
		if (target) {
			delete target;
			components.erase(target->getKey());
		}
	}

	template <class T> void Entity::disable() {
		T* c = get<T>();
		if (c) {
			c->disable();
		}
	}

	void Entity::disableAll() {
		for (auto c : components) {
			c.second->disable();
		}
	}

	template <class T> void Entity::enable() {
		T* c = get<T>();
		if (c) {
			c->enable();
		}
	}

	void Entity::enableAll() {
		for (auto c : components) {
			c.second->disable();
		}
	}

	template <class T> void Entity::toggle() {
		T* c = get<T>();
		if (c) {
			c->toggle();
		}
	}

	void Entity::toggleAll() {
		for (auto c : components) {
			c.second->toggle();
		}
	}
}
