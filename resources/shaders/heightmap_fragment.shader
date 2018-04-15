#version 330 core

in vec3 texture_coordinates;
in vec3 surface_normal;
in vec3 to_light;
in vec3 to_camera;

in float visibility;

out vec4 out_color;

uniform sampler2DArray textures;
uniform vec3 light_color;

const vec3 light_ambient = vec3(0.1, 0.1, 0.1);

const vec3 sky_color = vec3(0.3, 0.1, 0.0);

void main()
{
	vec3 unit_normal = normalize(surface_normal);
	vec3 unit_light	 = normalize(to_light);
	vec3 unit_camera = normalize(to_camera);

	vec3 light_direction = -to_camera;

	float normal_dot_light	= dot( unit_normal, unit_light );
	float brightness		= max( normal_dot_light, 0.0 );

	vec3 diffuse			 = brightness * light_color + light_ambient;
	vec3 reflected_light_dir = reflect ( light_direction, unit_normal );

	out_color = vec4 ( diffuse, 1.0 ) * texture( textures, texture_coordinates );
	out_color = mix ( vec4( sky_color, 1.0 ), out_color, visibility );
}