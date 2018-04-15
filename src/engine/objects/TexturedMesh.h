#pragma once

#include "Mesh.h"
#include "Texture.hpp"

class TexturedMesh : public Mesh {

	std::vector<Texture> textures;

public:

	TexturedMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements, const std::vector<Texture>& textures);

	std::vector<Texture>* get_textures();

	void draw(const ShaderProgram& program) override;

	~TexturedMesh();

};