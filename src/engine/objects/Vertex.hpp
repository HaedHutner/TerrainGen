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

	void calc_normal( const Vertex& v1, const Vertex& v2) {
		glm::vec3 va = position - v1.position;
		glm::vec3 vb = position - v2.position;

		normal = ( normal + glm::cross(va, vb) ) * 0.5f;
	}

	void cal_normal_2( void ( *height )( float, float, float ) ) {
		normal = glm::vec3(1, 1, 1);
	}
};