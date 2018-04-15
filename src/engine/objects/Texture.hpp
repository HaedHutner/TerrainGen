#pragma once

#include <string>

#include <assimp\scene.h>

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};