#version 330 core
in vec3 aPos;

out vec3 TexCoords;
out float visibility;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

const float density = 0.007;
const float gradient = 1.5;

void main()
{
	TexCoords = aPos;
	gl_Position = projection * view * model *  vec4(aPos, 1.0);

	vec4 positionRelativeToCamera = view * model * vec4(aPos, 1.0);
	float distance = 100.0f;
	visibility = exp(-pow((distance*density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}