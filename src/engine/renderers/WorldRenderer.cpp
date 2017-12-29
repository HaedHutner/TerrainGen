#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World * world, Light * sun, std::vector<std::string> ground_textures, Camera* camera, ShaderProgram program)
	: AbstractRenderer(program, camera), world ( world ), sun ( sun ), ground_textures ( 512, 512, ground_textures )
{
	shader_program.link();
}

void WorldRenderer::prepare()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader_program.use();

	shader_program.set_uniform_float("max_height", world->get_heightmap()->get_max_height());

	shader_program.set_uniform_vec3("light_position", sun->get_position());
	shader_program.set_uniform_vec3("light_color", sun->get_color());

	shader_program.set_uniform_mat4("model", glm::translate(glm::mat4(), world->get_heightmap()->get_position()));
	shader_program.set_uniform_mat4("view", camera->get_view());
	shader_program.set_uniform_mat4("projection", camera->get_projection());

	shader_program.set_uniform_int("textures", ground_textures.id());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void WorldRenderer::draw()
{
	std::vector<Chunk*> chunks = world->get_chunks_surrounding({ camera->get_position().x, camera->get_position().z }, glm::ivec2(2, 2));
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->get_terrain()->draw(shader_program);
	}
}

void WorldRenderer::post()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

WorldRenderer::~WorldRenderer()
{
	delete world;
	delete sun;
}
