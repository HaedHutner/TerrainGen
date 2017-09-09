#pragma once

#include <GL\glew.h>

class AbstractTexture {

protected:

	GLuint texture_id;
	int width, height, channels;

public:

	AbstractTexture();

	GLuint id();

	~AbstractTexture();

};