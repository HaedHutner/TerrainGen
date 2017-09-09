#include "HeightmapRenderer.h"

#ifdef PROCEDURAL
#define RENDER_RANGE 40
#endif


HeightmapRenderer::HeightmapRenderer(ShaderProgram shader_program, Camera* camera, Heightmap * heightmap, std::vector<std::string> groundTextures) 
	: AbstractRenderer(shader_program, camera), heightmap(heightmap),  ground_textures(512, 512, groundTextures)
{

#ifdef STATIC
	double timeBefore = glfwGetTime();
	heightmap->populate_raw(STATIC_SIZE_X, STATIC_SIZE_Y);
	double timeAfter = glfwGetTime();

	std::cout << "Generating Terrain Took " << timeAfter - timeBefore << " time units " << std::endl;

	vertex_buffer_size = heightmap->get_last_raw()->first.size();
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size * sizeof(Vertex), &heightmap->get_last_raw()->first[0], GL_STATIC_DRAW);

	element_buffer_size = heightmap->get_last_raw()->second.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_size * sizeof(GLuint), &heightmap->get_last_raw()->second[0], GL_STATIC_DRAW);
#endif
#ifdef PROCEDURAL
	update_vertices(camera);
#endif

	shader_program.link();
	shader_program.use();
	glBindFragDataLocation(shader_program.id(), 0, "out_color");

	shader_program.set_attribute("vertex_position", GL_FLOAT, GL_FALSE, 3, sizeof(Vertex), 0);
	shader_program.set_attribute("texture_coords",	GL_FLOAT, GL_FALSE, 3, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
	shader_program.set_attribute("normal",			GL_FLOAT, GL_FALSE, 3, sizeof(Vertex), (void*)(6 * sizeof(GLfloat)));

	sun_height = 1000.0f;
	sun = Light(glm::vec3( heightmap->get_position().x , sun_height, heightmap->get_position().z ), glm::vec3(0.5, 0.5, 0.5));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void HeightmapRenderer::prepare()
{
	glBindVertexArray(vertex_array);

#ifdef PROCEDURAL
	update_vertices(camera);
#endif

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_buffer_size * sizeof(Vertex), &heightmap->get_last_raw()->first[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, element_buffer_size * sizeof(GLuint), &heightmap->get_last_raw()->second[0]);

	shader_program.link();
	shader_program.use();

#ifndef CAMERA_SUN
	shader_program.set_uniform_vec3("light_position", sun.get_position());
	shader_program.set_uniform_vec3("light_color", sun.get_color());
#endif

#ifdef CAMERA_SUN
	shader_program.set_uniform_vec3("light_position", camera->get_position());
	shader_program.set_uniform_vec3("light_color", sun.get_color());
#endif

	shader_program.set_uniform_mat4("model", glm::translate(glm::mat4(),heightmap->get_position()));
	shader_program.set_uniform_mat4("view", camera->get_view());
	shader_program.set_uniform_mat4("projection", camera->get_projection());
	shader_program.set_uniform_int("textures", ground_textures.id());
}

void HeightmapRenderer::draw()
{
	glDrawElements(GL_TRIANGLES, element_buffer_size, GL_UNSIGNED_INT, 0);
}

void HeightmapRenderer::post()
{
	glBindVertexArray(0);
}

#ifdef PROCEDURAL
void HeightmapRenderer::update_vertices(Camera * camera) {

	float camX = camera->get_position().x;
	float camZ = camera->get_position().z;

	if (first_render || glm::distance(camera_last_coordinates, glm::vec2(camX, camZ)) >=  RENDER_RANGE ) {
		camera_last_coordinates.x = camX;
		camera_last_coordinates.y = camZ;
		if (first_render) first_render = false;

		heightmap->populate_raw_at_position(camZ, camX, RENDER_RANGE);

		vertex_buffer_size = heightmap->get_last_raw()->first.size();
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size * sizeof(Vertex), &heightmap->get_last_raw()->first[0], GL_STATIC_DRAW);

		element_buffer_size = heightmap->get_last_raw()->second.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_size * sizeof(GLuint), &heightmap->get_last_raw()->second[0], GL_STATIC_DRAW);
	}
}
#endif

HeightmapRenderer::~HeightmapRenderer() {
	delete heightmap;
}
