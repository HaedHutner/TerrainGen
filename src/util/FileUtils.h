#pragma once

#include <SOIL.h>

#include <string>
#include <fstream>
#include <vector>

#include "../engine/objects/Vertex.hpp"

#include "../game/Log.h"

namespace FileUtils {

	static std::string file_to_string(const std::string& file_path) {
		std::ifstream infile{ file_path };
		std::string content{ std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };

		return content;
	}

	static unsigned int texture_from_file(const char *path, const std::string &directory, bool gamma = false)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = SOIL_load_image(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			SOIL_free_image_data(data);
		}

		return textureID;
	}

	//static bool load_obj_file ( const std::string& file_path, std::vector<Vertex>& vertices ) {
	//	std::vector<unsigned int> vertexIndices, textureIndices, normalIndices;
	//	std::vector<glm::vec3> temp_position;
	//	std::vector<glm::vec2> temp_texture;
	//	std::vector<glm::vec3> temp_normal;

	//	FILE* file = fopen(file_path.c_str(), "r");

	//	if (file == NULL) {
	//		Log::error( "Could not open file " + file_path );
	//		return false;
	//	}

	//	while (true) {
	//		char lineHeader[128];

	//		int res = fscanf_s(file, "%s", lineHeader);
	//		if (res == EOF) break;

	//		if (strcmp(lineHeader, "v") == 0) { // if begins with "v", position
	//			glm::vec3 position;
	//			fscanf_s(file, "%f %f %f\n", &position.x, &position.y, &position.z);
	//			temp_position.push_back(position);
	//		}
	//		else if (strcmp(lineHeader, "vt")) { // if begins with "vt", texture
	//			glm::vec2 texture;
	//			fscanf_s(file, "%f %f\n", &texture.x, &texture.y);
	//			temp_texture.push_back(texture);
	//		}
	//		else if (strcmp(lineHeader, "vn") == 0) { // if begins with "vn", normal
	//			glm::vec3 normal;
	//			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
	//			temp_normal.push_back(normal);
	//		}
	//		else if (strcmp(lineHeader, "f") == 0) { // if begins with "f", triangle
	//			std::string vert1, vert2, vert3;
	//			unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
	//			int matches = fscanf_s(
	//				file,
	//				"%d/%d/%d %d/%d/%d %d/%d/%d\n",
	//				&vertexIndex[0], &textureIndex[0], &normalIndex[0],
	//				&vertexIndex[1], &textureIndex[1], &normalIndex[1],
	//				&vertexIndex[2], &textureIndex[2], &normalIndex[2]
	//			);

	//			if (matches != 9) {
	//				Log::error("Failed to match 9 vertex components.");
	//				return false;
	//			}

	//			vertices.push_back({});
	//		}
	//	}

	//	return true;
	//}

}