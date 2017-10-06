#pragma once

#include <glm\glm.hpp>
#include <map>
#include <vector>
#include <thread>

#include "Heightmap.h"
#include "Chunk.h"


class Chunk;

class World {

	Heightmap* heightmap;
	std::vector<Chunk*> chunks;

	glm::ivec2 chunk_size;

public:

	World ( Heightmap* heightmap, glm::ivec2 chunk_size );

	Heightmap* get_heightmap();

	void populate(glm::ivec2 start, glm::ivec2 end);

	std::vector<Chunk*> get_chunks();

	glm::ivec2 get_chunk_size();

	~World();

};