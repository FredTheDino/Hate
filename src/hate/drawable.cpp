#include "drawable.h"
#include <iostream>
#include "component.h"
#include "hate.h"

namespace hate {
	Drawable::Drawable(int layer) : Component() {
		this->layer = layer;
	}

	Drawable::~Drawable() {
		Hate::ENGINE->remove(this);
	}

	void Drawable::init() {
		Hate::ENGINE->add(this);
	}

	void Drawable::setLayer(int layer) {
		Hate::ENGINE->remove(this);
		this->layer = layer;
		Hate::ENGINE->add(this);
	}

	int Drawable::getLayer() {
		return layer;
	}

	void Drawable::draw() {}
}
