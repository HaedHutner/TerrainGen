#include "Chunk.h"

Chunk::Chunk(glm::ivec2 chunk_coordinates, World* world)
	: coordinates (chunk_coordinates)
{
	std::vector<Vertex> vertices( world->get_chunk_size().x * world->get_chunk_size().y + world->get_chunk_size().x + world->get_chunk_size().y + 1);
	std::vector<unsigned int> elements( world->get_chunk_size().x * world->get_chunk_size().y * 6 );

	glm::ivec2 begin( chunk_coordinates.x * world->get_chunk_size().x, chunk_coordinates.y * world->get_chunk_size().y );
	glm::ivec2 end( begin + world->get_chunk_size() );

	std::cout << "Generating chunk at " << begin.x << "; " << begin.y << " to " << end.x << "; " << end.y << ".\n";
	world->get_heightmap()->populate_elements( vertices, elements, begin, end);

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
