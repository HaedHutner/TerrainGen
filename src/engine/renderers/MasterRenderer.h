#pragma once

#include <vector>

#include "AbstractRenderer.h"
#include "../Camera.h"

class MasterRenderer {
private:

	std::vector<AbstractRenderer*> renderers;

	Camera* camera;

public:

	MasterRenderer( Camera* camera );

	void add_renderer(AbstractRenderer* renderer);

	void render();

	~MasterRenderer();
};
