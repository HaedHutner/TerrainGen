#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	Vertex() : position(glm::vec3()), uv(glm::vec2()), normal(glm::vec3()) {
	}

	Vertex(glm::vec3 xyz, glm::vec2 textureCoords, glm::vec3 normal) : position(xyz), uv(textureCoords), normal(normal) {}
};