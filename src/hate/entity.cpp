#include "entity.h"
#include "hate.h"
#include "entitymanager.h"

namespace hate {

	Entity::Entity(std::string name) {
		this->name = name;
		if (!name.empty())
			Hate::EM->add(this, name);
		else
			Hate::EM->add(this);
	}

	Entity::~Entity() {}

	void Entity::update(float delta) {

	}

	void Entity::draw() {
		if (drawable.canDraw()) {
			drawable.draw(transform.getMat());
		}
	}
}
