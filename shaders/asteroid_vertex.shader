#version 330 core

layout ( location = 0 ) in vec3 vertex_position;
layout ( location = 1 ) in vec3 texture_coords;
layout ( location = 2 ) in vec3 normal;

out vec3 TextureCoords;
out vec3 SurfaceNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	TextureCoords = texture_coords;
	SurfaceNormal = normal;
	gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}