#pragma once

#include <GL\glew.h>
#include <SOIL.h>

#include "AbstractTexture.h"

#include <string>

class Texture2D_RGB : public AbstractTexture{
public:
	Texture2D_RGB(const std::string& filepath);

	~Texture2D_RGB();

	void bind();

	void unbind();

	void set_param(GLenum parameter, GLint value);

	void set_single_param(GLenum parameter, GLint value);
};