#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Camera* camera) : camera(camera) {}

void MasterRenderer::add_renderer(AbstractRenderer * renderer) {
	renderers.push_back(renderer);
}

void MasterRenderer::render() {
	for (int i = renderers.size() - 1; i >= 0; i--) {
		renderers[i]->render();
	}
}

MasterRenderer::~MasterRenderer() {
	for (int i = 0; i < renderers.size(); i++) {
		delete renderers[i];
	}
}
