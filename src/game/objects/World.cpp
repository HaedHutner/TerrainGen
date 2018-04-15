#include "World.h"

World::World ( Heightmap* heightmap, glm::ivec2 chunk_size )
	: heightmap(heightmap), chunk_size(chunk_size)
{
}

Heightmap* World::get_heightmap()
{
	return heightmap;
}

Chunk* World::get_chunk(glm::ivec2 coordinates)
{
	for (int i = 0; i < chunks.size(); i++) {
		if (chunks[i]->get_coordinates() == coordinates) return chunks[i];
	}
	Chunk* chunk = new Chunk(coordinates, this);
	chunks.push_back(chunk);
	return chunk;
}

glm::ivec2 World::get_chunk_coordinates(glm::ivec2 position)
{
	return ( position / chunk_size );
}

std::vector<Chunk*> World::get_chunks_surrounding(glm::ivec2 position, glm::ivec2 size)
{
	printf("Surrounding Position: %d, %d\n", position.x, position.y);

	position = get_chunk_coordinates(position);
	glm::ivec2 start = position - size;
	glm::ivec2 end = position + size;

	printf("Rendering At Position: %d, %d from %d, %d to %d, %d\n", position.x, position.y, start.x, start.y, end.x, end.y);

	std::vector<Chunk*> final_chunks;

	for (int chunk_x = start.x; chunk_x < end.x; chunk_x++) {
		for (int chunk_y = start.y; chunk_y < end.y; chunk_y++) {
			final_chunks.push_back(get_chunk(glm::ivec2(chunk_x, chunk_y)));
		}
	}

	return final_chunks;
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
