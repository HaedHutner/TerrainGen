#pragma once

#include <GL\glew.h>

#include "Vertex.hpp"
#include "ShaderProgram.h"

#include <vector>

class Mesh {

	GLuint vertex_array, vertex_buffer, element_buffer;
	GLsizei vertex_buffer_size, element_buffer_size;

	std::vector<Vertex> vertices;
	std::vector<GLuint> elements;

	void setup();

public:

	Mesh();

	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& elements);

	std::vector<Vertex>* get_vertices();

	std::vector<GLuint>* get_elements();

	virtual void draw( const ShaderProgram& program );

	~Mesh();
};