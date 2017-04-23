#include "drawable.h"
#include <iostream>
#include "component.h"
#include "hate.h"

namespace hate {
	Drawable::Drawable() : Component() {
		Hate::ENGINE->add(this);
	}

	Drawable::~Drawable() {
		Hate::ENGINE->remove(this);
	}

	void Drawable::setLayer(int layer) {
		Hate::ENGINE->remove(this);
		this->layer = layer;
		Hate::ENGINE->add(this);
	}

	int Drawable::getLayer() {
		return layer;
	}

	void Drawable::draw() {
		std::cout << "DRAW!" << std::endl;
	}
}
