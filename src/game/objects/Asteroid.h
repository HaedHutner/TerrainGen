#pragma once

#include "../../noise/FastNoise.h"
#include "../../engine/objects/Vertex.hpp"
#include <math.h>
#include <glm\glm.hpp>
#include <vector>

class Asteroid {

	static FastNoise noise_generator;

	int seed;
	float radius;
	glm::vec3 position;

	std::pair<std::vector<Vertex>, std::vector<unsigned int>> raw;
	
public:

	Asteroid( glm::vec3 position, int seed, float radius);

	int get_seed();

	float get_radius();

	glm::vec3 get_position();

	std::pair<std::vector<Vertex>, std::vector<unsigned int>>* get_raw();

	~Asteroid();

private:

	void populate_vertices();

};