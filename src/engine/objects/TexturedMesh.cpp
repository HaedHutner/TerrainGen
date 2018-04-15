#include "TexturedMesh.h"

TexturedMesh::TexturedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements, const std::vector<Texture>& textures)
	: Mesh(vertices, elements), textures(textures)
{
}

std::vector<Texture>* TexturedMesh::get_textures()
{
	return &textures;
}

void TexturedMesh::draw(const ShaderProgram & program)
{
	unsigned int diffuse_num = 1;
	unsigned int specular_num = 1;
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse") {
			number = std::to_string(diffuse_num++);
		}
		else if (name == "texture_specular") {
			number = std::to_string(specular_num++);
		}

		program.set_uniform_float(("material." + name + number), i);

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glActiveTexture(GL_TEXTURE0);

	Mesh::draw(program);
}

TexturedMesh::~TexturedMesh() 
{
	
}