#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "TexturedMesh.h"

#include <string>
#include <vector>

#include "../../game/Log.h"
#include "../../util/FileUtils.h"

class Model {

	std::vector<Texture> loaded_textures;
	std::vector<TexturedMesh> meshes;
	std::string directory;

	void load(const std::string& path);

	void process_node(aiNode* node, const aiScene* scene);

	TexturedMesh process_mesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, const std::string& name);

public:

	Model(const std::string& path);

	void draw(const ShaderProgram& shader);

};