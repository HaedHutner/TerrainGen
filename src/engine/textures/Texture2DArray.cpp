#include "Texture2DArray.h"

Texture2DArray::Texture2DArray(int width, int height, const std::vector<std::string>& texturePaths) : num_textures(texturePaths.size()), width(width), height(height) {
	glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, num_textures, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	for (int i = 0; i < num_textures; i++) {
		unsigned char* image = SOIL_load_image(texturePaths[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
}

GLuint Texture2DArray::id() { return texture_id; }

Texture2DArray::~Texture2DArray() {
	glDeleteTextures(1, &texture_id);
}
