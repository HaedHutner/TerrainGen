#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& elements)
	: vertices(vertices), elements(elements)
{
	setup();
}

void Mesh::setup()
{
	glGenVertexArrays(1, &vertex_array);
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &element_buffer);

	glBindVertexArray(vertex_array);

	vertex_buffer_size = vertices.size() * sizeof(Vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, &vertices[0], GL_STATIC_DRAW);

	element_buffer_size = elements.size() * sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_size, &elements[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // positions at location 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

	glEnableVertexAttribArray(1); // texture coordinates at location 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) ( 3 * sizeof(GLfloat) ) );

	glEnableVertexAttribArray(2); // normals at location 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) ( 5 * sizeof(GLfloat) ) );

	glBindVertexArray(0);
}

std::vector<Vertex>* Mesh::get_vertices()
{
	return &vertices;
}

std::vector<GLuint>* Mesh::get_elements()
{
	return &elements;
}

void Mesh::draw(const ShaderProgram & program)
{
	glBindVertexArray(vertex_array);
	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &element_buffer);
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vertex_array);
}
