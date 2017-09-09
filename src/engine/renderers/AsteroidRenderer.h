#pragma once

#include "AbstractRenderer.h"

#include "../Vertex.h"
#include "../../game/objects/Asteroid.h"

#include <vector>

class AsteroidRenderer : public AbstractRenderer {

	std::vector<Asteroid*> asteroids;

	Asteroid* asteroid = new Asteroid( glm::vec3(0.0f, 0.0f, 100.0f), 1337, 10.0f);

public:

	AsteroidRenderer(ShaderProgram shaderProgram, Camera* camera);

	virtual void prepare() override;

	virtual void draw() override;

	virtual void post() override;

	~AsteroidRenderer();
};