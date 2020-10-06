#pragma once
#include <glm/glm.hpp>

class DirectinalLight
{
public:
	DirectinalLight() {};
	DirectinalLight(glm::vec3 _direction, glm::vec3 _color) : direction(_direction), color(_color) {};
	glm::vec3 direction = glm::vec3(0.0);
	glm::vec3 color = glm::vec3(color);
};