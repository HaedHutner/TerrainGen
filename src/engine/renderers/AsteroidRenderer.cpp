#include "AsteroidRenderer.h"

AsteroidRenderer::AsteroidRenderer(ShaderProgram shader_program, Camera * camera) 
	: AbstractRenderer(shader_program, camera)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	vertex_buffer_size = asteroid->get_raw()->first.size();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size * sizeof(Vertex), &asteroid->get_raw()->first[0], GL_STATIC_DRAW);

	shader_program.link();
	shader_program.use();

	glBindFragDataLocation(shader_program.id(), 0, "outColor");

	shader_program.set_attribute("vertex_position",		GL_FLOAT, GL_FALSE, 3, sizeof(Vertex), 0);
	shader_program.set_attribute("texture_coords",		GL_FLOAT, GL_FALSE, 3, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
	shader_program.set_attribute("normal",				GL_FLOAT, GL_FALSE, 3, sizeof(Vertex), (void*)(6 * sizeof(GLfloat)));

}

void AsteroidRenderer::prepare()
{
	glBindVertexArray(vertex_array);

	shader_program.use();

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	vertex_buffer_size = asteroid->get_raw()->first.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_buffer_size * sizeof(Vertex), &asteroid->get_raw()->first[0]);

	shader_program.set_uniform_mat4("model", glm::translate(glm::mat4(), asteroid->get_position()));
	shader_program.set_uniform_mat4("view", camera->get_view());
	shader_program.set_uniform_mat4("projection", camera->get_projection());
}

void AsteroidRenderer::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_size);
}

void AsteroidRenderer::post()
{
	glBindVertexArray(0);
}

AsteroidRenderer::~AsteroidRenderer()
{
	delete asteroid;
	for (int i = 0; i < asteroids.size(); i++) {
		delete asteroids[i];
	}
}
