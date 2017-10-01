#pragma once

#include <glm\glm.hpp>
#include <vector>

#include "World.h"
#include "../../engine/objects/Mesh.h"

class World;

class Chunk {

	glm::ivec2 coordinates;
	Mesh* terrain;

public:

	Chunk ( glm::ivec2 coordinates, World* world );

	glm::ivec2 get_coordinates();

	Mesh* get_terrain();

	~Chunk();

};