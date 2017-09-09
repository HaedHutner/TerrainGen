#pragma once

#include <GL\glew.h>
#include "../ShaderProgram.h"
#include "../Camera.h"

class AbstractRenderer {
protected:
	GLuint vertex_array;
	GLuint vertex_buffer;
	GLuint element_buffer;

	GLuint vertex_buffer_size;
	GLuint element_buffer_size;

	ShaderProgram shader_program;

	Camera* camera;
protected:

	AbstractRenderer(ShaderProgram shader_program, Camera* camera);;

	virtual void prepare() = 0;

	virtual void draw() = 0;

	virtual void post() = 0;

public:

	void render();

	~AbstractRenderer();
};