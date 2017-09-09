#include "Asteroid.h"

FastNoise Asteroid::noise_generator = FastNoise();

Asteroid::Asteroid( glm::vec3 position, int seed, float radius)
	: position(position)
{
	populate_vertices();
}

int Asteroid::get_seed()
{
	return seed;
}

float Asteroid::get_radius()
{
	return radius;
}

glm::vec3 Asteroid::get_position()
{
	return position;
}

std::pair<std::vector<Vertex>, std::vector<unsigned int>>* Asteroid::get_raw()
{
	return &raw;
}

void Asteroid::populate_vertices()
{
	const float PI = 3.1415926f;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// TODO Generate spherical vertices and change position relative to radial vector based on noise

	raw = std::pair<std::vector<Vertex>, std::vector<unsigned int>>(vertices, indices);
}

Asteroid::~Asteroid()
{
}
