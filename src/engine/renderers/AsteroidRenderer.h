#pragma once

#include "AbstractRenderer.h"

#include "../objects/Vertex.hpp"
#include "../../game/objects/Asteroid.h"

#include <vector>

class AsteroidRenderer : public AbstractRenderer {

	GLuint vertex_array, vertex_buffer, element_buffer;
	GLsizei vertex_buffer_size, element_buffer_size;

	std::vector<Asteroid*> asteroids;

	Asteroid* asteroid = new Asteroid( glm::vec3(0.0f, 0.0f, 100.0f), 1337, 10.0f);

public:

	AsteroidRenderer(ShaderProgram shaderProgram, Camera* camera);

	virtual void prepare() override;

	virtual void draw() override;

	virtual void post() override;

	~AsteroidRenderer();
};