#pragma once

#include <GL\glew.h>
#include <SOIL.h>

#include <vector>

class Texture2DArray {
private:
	GLuint texture_id;

	GLubyte num_textures;
	GLsizei width;
	GLsizei height;

public:

	Texture2DArray(int width, int height, const std::vector<std::string>& texturePaths);

	GLuint id();

	~Texture2DArray();
};