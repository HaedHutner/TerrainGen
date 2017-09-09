#pragma once

#include <GL/glew.h>
#include <SOIL.h>

#include "AbstractTexture.h"
#include "../../game/Log.h"

#include <string>
#include <vector>

class CubemapTexture : public AbstractTexture {

public:

	CubemapTexture(std::vector<std::string>& paths);

 };