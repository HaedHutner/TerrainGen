#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(const ShaderProgram & program, Camera * camera, std::vector<Model*> models)
	: AbstractRenderer(program, camera), models(models)
{
}

void ModelRenderer::add(Model * model)
{
	models.push_back(model);
}

void ModelRenderer::prepare()
{
	shader_program.use();

	shader_program.set_uniform_mat4("view", camera->get_view());
	shader_program.set_uniform_mat4("projection", camera->get_projection());
}

void ModelRenderer::draw()
{
	for (int i = 0; i < models.size(); i++) {
		shader_program.set_uniform_mat4("model", glm::mat4());
		models[i]->draw(shader_program);
	}
}

void ModelRenderer::post()
{
}

ModelRenderer::~ModelRenderer()
{
	for (int i = 0; i < models.size(); i++) {
		delete models[i];
	}
}
