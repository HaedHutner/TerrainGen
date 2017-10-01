#include "World.h"

World::World ( Heightmap* heightmap, glm::ivec2 chunk_size )
	: heightmap(heightmap), chunk_size(chunk_size)
{
	for (int chunk_x = -2; chunk_x < 4; chunk_x++) {
		for (int chunk_y = -2; chunk_y < 4; chunk_y++) {
			chunks.push_back(new Chunk( glm::ivec2(chunk_x, chunk_y), this ) );
		}
	}
}

Heightmap* World::get_heightmap()
{
	return heightmap;
}

std::vector<Chunk*> World::get_chunks()
{
	return chunks;
}

glm::ivec2 World::get_chunk_size()
{
	return chunk_size;
}

World::~World() {
	delete heightmap;
	for (int i = 0; i < chunks.size(); i++) {
		delete chunks[i];
	}
}
