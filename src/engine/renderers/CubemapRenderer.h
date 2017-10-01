#pragma once

#include <GL\glew.h>

#include <vector>

#include "AbstractRenderer.h"
#include "..\textures\CubemapTexture.h"
#include "..\objects\ShaderProgram.h"
#include "..\..\game\objects\Skybox.h"

class CubemapRenderer : public AbstractRenderer {
private:

	GLuint vertex_array, vertex_buffer, element_buffer;
	GLsizei vertex_buffer_size, element_buffer_size;

	Skybox* skybox;

protected:

	virtual void prepare() override;

	virtual void draw() override;

	virtual void post() override;

public:
	CubemapRenderer(ShaderProgram shaderProgram, Camera* camera, Skybox* skybox);

	~CubemapRenderer();
};
