#include "renderengine.h"

namespace hate {
	RenderEngine::RenderEngine() {}

	RenderEngine::~RenderEngine() {}

	void RenderEngine::add(Drawable* drawable) {
		layers[drawable->getLayer()].push_back(drawable);
	}

	void RenderEngine::remove(Drawable* drawable) {
		auto layer = layers[drawable->getLayer()];
		for (int i = 0; i < layer.size(); i++) {
			if (layer[i] == drawable) {
				layer.erase(layer.begin() + i);
			}
		}
	}

	/*
	void RenderEngine::draw() {
		for (auto layer : layers) {
			for (Drawable* d : layer.second) {
				d->draw();
			}
		}
	}
	*/
}
