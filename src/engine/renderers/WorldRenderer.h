#pragma once

#include "AbstractRenderer.h"
#include "../textures/Texture2DArray.h"

#include "../../game/objects/World.h"
#include "../../game/objects/Light.h"

class WorldRenderer : public AbstractRenderer {

	Light* sun;
	World* world;
	Texture2DArray ground_textures;

	virtual void prepare() override;
	virtual void draw() override;
	virtual void post() override;

public: 

	WorldRenderer(World* world, Light* sun, std::vector<std::string> ground_textures, Camera* camera, ShaderProgram program);

	~WorldRenderer();
};
