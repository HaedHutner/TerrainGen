#pragma once

#include <GL\glew.h>
#include "../objects/ShaderProgram.h"
#include "../objects/Camera.h"

class AbstractRenderer {
protected:

	ShaderProgram shader_program;

	Camera* camera;
protected:

	AbstractRenderer(const ShaderProgram& shader_program, Camera* camera);;

	virtual void prepare() = 0;

	virtual void draw() = 0;

	virtual void post() = 0;

public:

	void render();

	~AbstractRenderer();
};