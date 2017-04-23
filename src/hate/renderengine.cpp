#include "renderengine.h"
#include <iostream>

namespace hate {
	RenderEngine::RenderEngine() {}

	RenderEngine::~RenderEngine() {}

	void RenderEngine::add(Drawable* drawable) {
		layers[drawable->getLayer()].push_back(drawable);
	}

	void RenderEngine::remove(Drawable* drawable) {
		auto layer = layers[drawable->getLayer()];
		int i;
		for (; i < layer.size(); i++) {
			if (layer[i] == drawable) break;
		}
		layer.erase(layer.begin() + i);
	}

	void RenderEngine::draw() {
		for (auto layer : layers) {
			for (size_t i = 0; i < layer.second.size(); i++) {
				Drawable* d = layer.second[i];
				d->draw();
			}
		}
	}
}
