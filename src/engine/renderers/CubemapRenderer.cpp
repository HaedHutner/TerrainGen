#include "CubemapRenderer.h"

CubemapRenderer::CubemapRenderer(ShaderProgram shader_program, Camera* camera, Skybox* skybox) : AbstractRenderer(shader_program, camera), skybox(skybox)
{
	vertex_buffer_size = skybox->Vertices.size();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size * sizeof(GLfloat), &skybox->Vertices[0], GL_STATIC_DRAW);

	shader_program.link();
	shader_program.use();
	shader_program.set_attribute("aPos", GL_FLOAT, GL_FALSE, 3, 3 * sizeof(GLfloat), 0);
}

void CubemapRenderer::prepare()
{
	glDisable(GL_CULL_FACE);

	glBindVertexArray(vertex_array);
	glDepthMask(GL_FALSE);
	
	shader_program.use();
	shader_program.set_uniform_mat4("model",		glm::translate(glm::mat4(), camera->get_position()));
	shader_program.set_uniform_mat4("projection",	camera->get_projection());
	shader_program.set_uniform_mat4("view",			camera->get_view());

	shader_program.set_uniform_int("skybox", skybox->TextureId());
}

void CubemapRenderer::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_size);
}

void CubemapRenderer::post()
{
	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
}

CubemapRenderer::~CubemapRenderer()
{
	delete skybox;
}
