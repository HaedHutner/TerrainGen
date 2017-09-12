#version 330 core

in vec3 TextureCoords;
in vec3 SurfaceNormal;

out vec4 outColor;

void main() {
	outColor = vec4(0.0, 0.0, 1.0, 1.0);
}