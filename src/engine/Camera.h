#pragma once

#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Camera {
private:
	float last_frame = 0;
	float delta_time = 0;

	float speed_modifyer = 2.5f;
	float mouse_sensitivity = 0.2f;

	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_direction = glm::normalize(camera_position - camera_target);

	glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camera_right = glm::normalize(glm::cross(camera_up, camera_direction));

	glm::mat4 projection;

	bool first_mouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float last_x;
	float last_y;
	float field_of_view = 90.0f;
public:
	enum MoveDirection {
		UP,
		DOWN,
		FORWARD,
		BACK,
		LEFT,
		RIGHT
	};

	Camera(float fov, float cameraSpeed, float mouseSensitivity, int screenX, int screenY, glm::vec3 beginningCoords = { 0, 0, 0 }, glm::vec3 beginningDirection = { 0, 0, 0 }, glm::vec2 beginningRotation = { 0, 0 });

	~Camera();

	glm::mat4 get_view();

	glm::mat4 get_projection();

	glm::vec3 get_position();

	void update_projection(int screenX, int screenY);

	void reset_cursor(float x, float y);

	void move(MoveDirection dir, float speed);

	void process_key_input(GLFWwindow* window);

	void process_mouse_input(GLFWwindow* window, double x, double y);
};