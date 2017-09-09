#include "CubemapTexture.h"

CubemapTexture::CubemapTexture(std::vector<std::string>& paths)
	: AbstractTexture()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

	for (int i = 0; i < paths.size(); i++) {
		unsigned char* data = SOIL_load_image(paths[i].c_str(), &width, &height, &channels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			Log::error("Cubemap Texture at path " + paths[i] + " failed to load.");
		}
		SOIL_free_image_data(data);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
