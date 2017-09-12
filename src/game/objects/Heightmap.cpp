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

	std::vector<Vertex> vertices( (width - offsetX) * ( height - offsetY));
	std::vector<unsigned int> indices( (width - offsetX) * (height - offsetY) * 6);
	add_vertices_3(vertices, indices, glm::vec2 ( offsetX, offsetY ), glm::vec2 ( height, width ) );

	last_raw = std::pair<std::vector<Vertex>, std::vector<unsigned int>>(vertices, indices);
}

// for procedural drawing
void Heightmap::populate_raw_at_position(int camX, int camZ, int range) {

	int width = 2*range;
	int height = 2*range;

	while (camX != 0 && camX % resolution != 0) camX++;
	while (camZ != 0 && camZ % resolution != 0) camZ++;

	std::vector<Vertex> vertices( height * width );
	std::vector<unsigned int> indices( height * width * 6 );
	
	add_vertices_3(vertices, indices, glm::vec2( ( camZ - range ), ( camX - range ) ), glm::vec2( ( camZ + range ), ( camX + range ) ) );

	last_raw = std::pair<std::vector<Vertex>, std::vector<unsigned int>>(vertices, indices);
}

glm::vec3 Heightmap::get_position()
{
	return position;
}

float Heightmap::get_max_height() {
	return max_height;
}

std::pair<std::vector<Vertex>, std::vector<unsigned int>>* Heightmap::get_last_raw()
{
	return &last_raw;
}

Heightmap::~Heightmap()
{
}

void Heightmap::add_vertices_3(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, const glm::vec2& begin, const glm::vec2& end)
{
	glm::vec2 size = end - begin;

	int width = (int) size.x;
	int height = (int) size.y;

	float u = 0.0f;
	float v = size.y * texture_resolution;

	float lastZ = begin.y;

	float beginX = begin.x;
	float beginY = begin.y;

	int j = 0;

	for (int i = 0; i < vertices.size(); i++) {

		float x = ( i % width + beginX) * resolution;

		x == beginX ? u = 0.0f : u += 1.0f * texture_resolution; // for every increase in x, increase tX, and reset tX to 0 when x = 0

		float z = ( i / width + beginY) * resolution;

		if (z != lastZ) { // for every increase in z, decrease tY
			v -= 1.0f * texture_resolution;
			lastZ+= resolution;
		}

		const FN_DECIMAL y = get_value_at(x, z, max_height);
		vertices[i].position = { (float) x, (float) y, (float) z };
		vertices[i].uv = { u, v };
		//vertices[i].normal = { 0, 0, 0 };

		if (z == beginY * resolution || x == beginX * resolution) {
			// a vertex with either z or x equaling their beginning values is missing neighboring vertices requried to construct the quad
			// just add vertex to vertices vector and continue
			continue;
		} 
		else if (z != beginY * resolution && x != beginX * resolution) {
			// movement on both axis
			// there are vertices prior to this one on the row
			// there is at least 1 row above this one
			// there is enough information to construct a quad
			// generate this vertex, find indices of other 3 vertices, calculate normals and save their indices

			const int e[4] = {
				i - (int) size.y - 1,	// upper - left
				i - 1,					// left
				i - (int) size.y,		// up
				i						// this
			};

			Vertex* v1 = &vertices[e[0]];
			Vertex* v2 = &vertices[e[1]];
			Vertex* v3 = &vertices[e[2]];
			Vertex* v4 = &vertices[e[3]];

			v1->calc_normal(*v2, *v3);
			v2->calc_normal(*v1, *v3);
			v3->calc_normal(*v2, *v4);
			v4->calc_normal(*v2, *v3);

			indices[j + 0] = e[0];
			indices[j + 1] = e[1];
			indices[j + 2] = e[2];
			indices[j + 3] = e[2];
			indices[j + 4] = e[1];
			indices[j + 5] = e[3];

			j += 6;
		}
	}
}


FN_DECIMAL Heightmap::get_value_at(FN_DECIMAL x, FN_DECIMAL y, FN_DECIMAL amplification) {
	return amplification * ( ( ( noise_generator.GetNoise(x, y) + (FN_DECIMAL) 0.5f ) * (noise_generator.GetCellular(x, y) ) ) - (FN_DECIMAL) 0.7f );
}

Heightmap::Material Heightmap::get_material_at ( float height )
{
	return height <= 0.0f ? (height <= -2 * (max_height / 4) ? SAND : GRASS) : (height >= 2 * (max_height / 4) ? ROCK : GRAVEL);
}
