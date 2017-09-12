#version 430 core

in vec3 vertex_position;
in vec2 texture_coords;
in vec3 normal;

out vec3 texture_coordinates;
out vec3 surface_normal;
out vec3 to_light;
out vec3 to_camera;
out float visibility;

uniform float max_height;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 light_position;

const float fog_density = 0.002;
const float fog_gradient = 1.5;

int get_material_at(float height)
{
	return height <= 0.0f ? ( height <= -2 * (max_height / 4) ? 3 : 2 ) : (height >= 2 * ( max_height / 4 ) ? 0 : 1);
}

void main()
{
	vec4 world_position = model * vec4( vertex_position, 1.0 );

	vec4 position_relative_to_camera = view * world_position;

	surface_normal		= ( model * vec4(normal, 0.0) ).xyz;
	to_light			= light_position - world_position.xyz;
	to_camera			= ( inverse( view ) * vec4( 0.0, 0.0, 0.0, 1.0 ) ).xyz - world_position.xyz;
	texture_coordinates	= vec3 ( texture_coords, get_material_at ( vertex_position.y ) );

	float distance	= length( position_relative_to_camera.xyz );
	visibility		= exp( -pow( ( distance*fog_density ), fog_gradient ) );
	visibility		= clamp( visibility, 0.0, 1.0 );

	gl_Position		= projection * position_relative_to_camera;
}