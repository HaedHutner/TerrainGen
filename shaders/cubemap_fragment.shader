#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
in float visibility;

uniform samplerCube skybox;

const vec3 skyColor = vec3(0.3, 0.1, 0.0);

void main()
{
	FragColor = texture(skybox, TexCoords);
	FragColor = mix(vec4(skyColor, 1.0), FragColor, visibility);
}