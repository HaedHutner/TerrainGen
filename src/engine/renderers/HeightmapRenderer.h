#pragma once

#include <GL\glew.h>

#include "AbstractRenderer.h"

#include "../textures/Texture2DArray.h"

#include "../../game/objects/Light.h"
#include "../../game/objects/Heightmap.h"
#include "../../game/Log.h"

#include "../Vertex.h"

#define STATIC_SIZE_X 512
#define STATIC_SIZE_Y 512

#define STATIC
#define STATIC_SUN

class HeightmapRenderer : public AbstractRenderer {
private:
	Heightmap* heightmap;

	Texture2DArray ground_textures;

	Light sun;
	float sun_height;

#ifdef MOVING_SUN

	double t = 0;
	float _lastFrame = 0;
	float _deltaTime = 0;

#endif

	GLuint light_vertex_array;

#ifdef PROCEDURAL

	glm::vec2 camera_last_coordinates = glm::vec2(0.0f, 0.0f);
	bool first_render = true;

#endif

public:
	HeightmapRenderer(ShaderProgram shader_program, Camera* camera, Heightmap* heightmap, std::vector<std::string> groundTextures);

#ifdef PROCEDURAL
	void update_vertices(Camera* camera);
#endif

	virtual void prepare() override;
	virtual void draw() override;
	virtual void post() override;

	~HeightmapRenderer();
};