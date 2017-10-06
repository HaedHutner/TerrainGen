#include "World.h"

World::World ( Heightmap* heightmap, glm::ivec2 chunk_size )
	: heightmap(heightmap), chunk_size(chunk_size)
{
	populate(glm::ivec2(-2, -2), glm::ivec2(2, 2));
}

Heightmap* World::get_heightmap()
{
	return heightmap;
}

void World::populate(glm::ivec2 start, glm::ivec2 end)
{
	std::vector<std::thread> threads;
	
	for (int chunk_x = start.x; chunk_x < end.x; chunk_x++) {
		for (int chunk_y = start.y; chunk_y < end.y; chunk_y++) {
			//threads.push_back(std::thread([&] {
				chunks.push_back(new Chunk(glm::ivec2(chunk_x, chunk_y), this));
			//}));
		}
	}
	
	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}

	//for (int chunk_x = start.x; chunk_x < end.x; chunk_x++) {
	//	for (int chunk_y = start.y; chunk_y < end.y; chunk_y++) {
	//		chunks.push_back(new Chunk(glm::ivec2(chunk_x, chunk_y), this));
	//	}
	//}
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
