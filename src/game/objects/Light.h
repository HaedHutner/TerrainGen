#pragma once

#include <glm\glm.hpp>

class Light {

	glm::vec3 position;
	glm::vec3 color;

public:

	Light();

	Light(glm::vec3 position, glm::vec3 color);

	glm::vec3 get_position();

	glm::vec3 get_color();
};
