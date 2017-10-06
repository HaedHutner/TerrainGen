#include "Heightmap.h"

// For static drawing

Heightmap::Heightmap(int seed, FastNoise::NoiseType type, FastNoise::FractalType fractalType, glm::vec3 position, float textureRes, int octaves, int resolution, float maxHeight)
	: resolution(resolution), max_height(maxHeight), texture_resolution(textureRes), position(position)
{
	noise_generator = FastNoise(seed);
	noise_generator.SetNoiseType(type);
	noise_generator.SetFractalType(fractalType);
	noise_generator.SetFractalOctaves(octaves);

	noise_generator.SetCellularDistanceFunction(FastNoise::CellularDistanceFunction::Euclidean);
	noise_generator.SetCellularReturnType(FastNoise::CellularReturnType::Distance2Add);
	noise_generator.SetFrequency(0.004f);
	noise_generator.SetInterp(FastNoise::Interp::Quintic);
}

// for static drawing
void Heightmap::populate_raw(int height, int width) {
	position = glm::vec3(-width * resolution / 2, 0, -height * resolution / 2);

	int offsetX = 0;
	int offsetY = 0;

	glm::vec2 begin(offsetX, offsetY);
	glm::vec2 end(height, width);

	glm::vec2 size = end - begin;

	std::vector<Vertex> vertices( (int) size.x * size.y );
	std::vector<unsigned int> indices( (int) size.x * size.y * 6);
	add_vertices_4(vertices, indices, begin, end );

	last_raw = new Mesh(vertices, indices);
}

// for procedural drawing
void Heightmap::populate_raw_at_position(int camX, int camZ, int range) {

	int width = 2*range;
	int height = 2*range;

	while (camX != 0 && camX % resolution != 0) camX++;
	while (camZ != 0 && camZ % resolution != 0) camZ++;

	std::vector<Vertex> vertices( height * width );
	std::vector<unsigned int> indices( height * width * 6 );
	
	add_vertices_4(vertices, indices, glm::vec2( ( camZ - range ), ( camX - range ) ), glm::vec2( ( camZ + range ), ( camX + range ) ) );

	last_raw = new Mesh(vertices, indices);
}

void Heightmap::populate_elements(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const glm::vec2 & begin, const glm::vec2 & end)
{
	add_vertices_4(vertices, indices, begin, end);
}

glm::vec3 Heightmap::get_position()
{
	return position;
}

float Heightmap::get_max_height() {
	return max_height;
}

Mesh* Heightmap::get_last_raw()
{
	return last_raw;
}

Heightmap::~Heightmap()
{
	delete last_raw;
}

void Heightmap::add_vertices_4(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const glm::ivec2& begin, const glm::ivec2& end) {

	glm::ivec2 size = end - begin + glm::ivec2(1,1);

	int j = 0;
	int i = 0;

	// generate mesh
	for (i = 0; i < vertices.size(); i++) {
		const int chunk_x = i % (size.y);
		const int chunk_z = i / (size.y);

		const int e[4] = {
			i,					// this
			i - 1,				// left
			i - (size.y),		// bottom
			i - (size.y) - 1    // bottom - left
		};

		const float x = (i % size.y + begin.x) * resolution;
		const float z = (i / size.y + begin.y) * resolution;

		const FN_DECIMAL y = get_value_at(x, z, max_height);
		vertices[i].position = { (float)x, (float)y, (float)z };
		vertices[i].uv = { chunk_x * texture_resolution, chunk_z * texture_resolution };

		if (chunk_x != 0 && chunk_z != 0) {

			indices[j + 0] = e[0];
			indices[j + 1] = e[1];
			indices[j + 2] = e[2];
			indices[j + 3] = e[2];
			indices[j + 4] = e[1];
			indices[j + 5] = e[3];

			j += 6;
		}
	}

	// calc normals
	for (int i = 0; i < vertices.size(); i++) {
		// Required verts: x + 1, y + 1; x + 1, y - 1; x - 1; y + 1; x - 1; y - 1
		// Calculate i at each
		// if new index is less than i, the vertex has already been generated
		// if new index is more than i, the vertex has not yet been generated
		// if the vertex has already been generated, get it from the vertices vector and use the data
		// if the vertex has not yet been generated, generate a new value at those coordinates.

		const float x = (i % size.y + begin.x) * resolution;
		const float z = (i / size.y + begin.y) * resolution;

		float hA = x == end.x * resolution || x == begin.x * resolution || (i + size.y + 1) >= vertices.size() ? get_value_at(x + resolution, z + resolution) : vertices[i + size.x + 1].position.y / max_height;
		float hC = x == end.x * resolution || x == begin.x * resolution || (i - size.y - 1) <= 0 ? get_value_at(x - resolution, z - resolution) : vertices[i - size.x - 1].position.y / max_height;
		float hD = x == end.x * resolution || x == begin.x * resolution || (i - size.y + 1) <= 0 ? get_value_at(x + resolution, z - resolution) : vertices[i - size.x + 1].position.y / max_height;
		float hB = x == end.x * resolution || x == begin.x * resolution || (i + size.y - 1) >= vertices.size() ? get_value_at(x - resolution, z + resolution) : vertices[i + size.x - 1].position.y / max_height;

		vertices[i].normal = glm::normalize(glm::vec3(hA - hC, 0.1, hD - hB));
	}
}


FN_DECIMAL Heightmap::get_value_at(FN_DECIMAL x, FN_DECIMAL y, FN_DECIMAL amplification) {
	return amplification * ( ( ( noise_generator.GetNoise(x, y) + (FN_DECIMAL) 0.5f ) * (noise_generator.GetCellular(x, y) ) ) - (FN_DECIMAL) 0.7f );
}

glm::vec3 Heightmap::get_normal_at(FN_DECIMAL x, FN_DECIMAL y, FN_DECIMAL amplification)
{
	float hL = get_value_at(x - resolution, y - resolution);
	float hR = get_value_at(x + resolution, y + resolution);
	float hD = get_value_at(x + resolution, y - resolution);
	float hU = get_value_at(x - resolution, y + resolution);

	return glm::normalize( glm::vec3( hL - hR, 0.1, hD - hU ) );
}

Heightmap::Material Heightmap::get_material_at ( float height )
{
	return height <= 0.0f ? (height <= -2 * (max_height / 4) ? SAND : GRASS) : (height >= 2 * (max_height / 4) ? ROCK : GRAVEL);
}
