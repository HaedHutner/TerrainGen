#pragma once

#include <CImg.h>

#include <math.h>
#include <vector>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>

#include "../../noise/FastNoise.h"
#include "../../engine/objects/Vertex.hpp"
#include "../../engine/objects/Mesh.h"
#include "Light.h"

class Heightmap {

	FastNoise noise_generator;

	int resolution;
	float max_height;
	float texture_resolution;

	glm::vec3 position;

	Mesh* last_raw;

	enum Material {
		ROCK = 0,
		GRAVEL = 1,
		GRASS = 2,
		SAND = 3
	};

public:

	Heightmap(int seed, FastNoise::NoiseType type, FastNoise::FractalType fractalType, glm::vec3 position, float textureRes = 0.5f, int octaves = 5, int resolution = 4, float maxHeight = 64.0f);

	Heightmap(const Heightmap&) = delete;

	// For static drawing
	void populate_raw(int height, int width);

	// for procedural drawing
	void populate_raw_at_position(int camX, int camZ, int range = 10);

	void populate_elements(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const glm::vec2& begin, const glm::vec2& end);

	glm::vec3 get_position();

	float get_max_height();

	Mesh* get_last_raw();

	~Heightmap();

private:

	void add_vertices_3(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const glm::vec2& begin, const glm::vec2& end);

	FN_DECIMAL get_value_at(FN_DECIMAL x, FN_DECIMAL y, FN_DECIMAL amplification = 1.0f);

	Material get_material_at( float height );
};