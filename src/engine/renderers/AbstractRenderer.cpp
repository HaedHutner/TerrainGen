#include "AbstractRenderer.h"

AbstractRenderer::AbstractRenderer(ShaderProgram shader_program, Camera * camera) : shader_program(shader_program), camera(camera) {
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
}

void AbstractRenderer::render() {
	prepare();
	draw();
	post();
}

AbstractRenderer::~AbstractRenderer() {
	glDeleteBuffers(1, &element_buffer);
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vertex_array);
	shader_program.clear();
}
