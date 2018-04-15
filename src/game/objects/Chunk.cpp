#include "Chunk.h"

Chunk::Chunk(glm::ivec2 chunk_coordinates, World* world)
	: coordinates (chunk_coordinates), parent(world)
{
	generate_terrain();
}

void Chunk::generate_terrain()
{
	std::vector<Vertex> vertices(parent->get_chunk_size().x * parent->get_chunk_size().y + parent->get_chunk_size().x + parent->get_chunk_size().y + 1);
	std::vector<unsigned int> elements(parent->get_chunk_size().x * parent->get_chunk_size().y * 6);

	glm::ivec2 begin(coordinates.x * parent->get_chunk_size().x, coordinates.y * parent->get_chunk_size().y);
	glm::ivec2 end(begin + parent->get_chunk_size());

	std::cout << "Generating chunk at " << begin.x << "; " << begin.y << " to " << end.x << "; " << end.y << ".\n";

	std::thread thread([&] {
		parent->get_heightmap()->populate_elements(vertices, elements, begin, end);
	});
	thread.join();
	terrain = new Mesh(vertices, elements);
}

glm::ivec2 Chunk::get_coordinates()
{
	return coordinates;
}

Mesh* Chunk::get_terrain()
{
	return terrain;
}

Chunk::~Chunk()
{
	delete terrain;
}
