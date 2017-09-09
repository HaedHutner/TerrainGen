#include "Texture2D_RGB.h"

Texture2D_RGB::Texture2D_RGB(const std::string& filepath) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image = SOIL_load_image(filepath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}

Texture2D_RGB::~Texture2D_RGB() {
	glDeleteTextures(1, &texture_id);
}

void Texture2D_RGB::bind() {
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture2D_RGB::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D_RGB::set_param(GLenum parameter, GLint value) {
	glTexParameteri(GL_TEXTURE_2D, parameter, value);
}

void Texture2D_RGB::set_single_param(GLenum parameter, GLint value) {
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, parameter, value);
	glBindTexture(GL_TEXTURE_2D, 0);
}
