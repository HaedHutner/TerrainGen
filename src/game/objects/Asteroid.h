#pragma once

#include "../../engine/objects/Mesh.h"
#include "../../noise/FastNoise.h"
#include <math.h>
#include <glm\glm.hpp>
#include <vector>

class Asteroid {

	static FastNoise noise_generator;



	int seed;
	float radius;
	glm::vec3 position;

	Mesh* mesh;
	
public:

	Asteroid( glm::vec3 position, int seed, float radius);

	int get_seed();

	float get_radius();

	glm::vec3 get_position();

	Mesh* get_mesh();

	~Asteroid();

private:

	void populate_vertices();

};