#include "AbstractRenderer.h"

AbstractRenderer::AbstractRenderer(const ShaderProgram& shader_program, Camera * camera) : shader_program(shader_program), camera(camera) {
}

void AbstractRenderer::render() {
	prepare();
	draw();
	post();
}

AbstractRenderer::~AbstractRenderer() {
	shader_program.clear();
}
