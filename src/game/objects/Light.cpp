#include "Light.h"

Light::Light() : position(0, 0, 0), color(1.0, 1.0, 1.0) {

}

Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) {

}

glm::vec3 Light::get_position() {
	return position;
}

glm::vec3 Light::get_color() {
	return color;
}
