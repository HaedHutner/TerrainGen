#pragma once

#include <glm\glm.hpp>
#include <vector>

#include "World.h"
#include "../../engine/objects/Mesh.h"

class World;

class Chunk {

	World* parent;
	glm::ivec2 coordinates;
	Mesh* terrain;

public:

	Chunk ( glm::ivec2 coordinates, World* world );

	void generate_terrain();

	glm::ivec2 get_coordinates();

	Mesh* get_terrain();

	~Chunk();

};