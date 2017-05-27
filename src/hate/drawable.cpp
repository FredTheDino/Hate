#include "drawable.h"
#include <iostream>
#include "component.h"
#include "hate.h"

namespace hate {
	Drawable::Drawable() {};

	Drawable::Drawable(const char* path, int layer) {
		init(std::string(path), layer);
	}

	Drawable::Drawable(std::string path, int layer) {
		init(path, layer);
	}

	void Drawable::init(std::string path, int layer) {
		this->layer = layer;
		mesh = Hate::LOADER->loadMesh(path);
		//Hate::ENGINE->add(this);
	}

	Drawable::~Drawable() {
		//Hate::ENGINE->remove(this);
		//Hate::ENGINE->add(this);
	}

	bool Drawable::canDraw() {
		return mesh != nullptr;
	}
	
	void Drawable::setLayer(int layer) {
		//Hate::ENGINE->remove(this);
		this->layer = layer;
		//Hate::ENGINE->add(this);
	}

	int Drawable::getLayer() {
		return layer;
	}

	void Drawable::draw(Mat4 m) {
		if (mesh) {
			glUniformMatrix4fv(Hate::SHADER->location("model"), &m._01 - &m._00, GL_FALSE, &m._00);
			/*
			for (int i = 0; i < NUM_TEXTURES; i++) {
				if (textures[i]) {
					textures[i]->bind(i);
				}
			}
			*/
			mesh->draw();
		}
	}
}
