#pragma once

#include "AbstractRenderer.h"
#include "../objects/Model.h"

#include <vector>

class ModelRenderer : public AbstractRenderer {

	std::vector<Model*> models;

	virtual void prepare() override;
	virtual void draw() override;
	virtual void post() override;

public:

	ModelRenderer(const ShaderProgram& program, Camera* camera, std::vector<Model*> models);

	void add(Model* model);

	~ModelRenderer();

};