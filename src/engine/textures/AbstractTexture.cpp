#include "AbstractTexture.h"

AbstractTexture::AbstractTexture()
{
	glGenTextures(1, &texture_id);
	glActiveTexture(GL_TEXTURE0 + texture_id);
}

GLuint AbstractTexture::id()
{
	return texture_id;
}

AbstractTexture::~AbstractTexture()
{
	glDeleteTextures(1, &texture_id);
}
