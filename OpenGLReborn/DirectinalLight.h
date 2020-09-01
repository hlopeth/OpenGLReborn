#pragma once
#include <glm/glm.hpp>

class DirectinalLight
{
public:
	DirectinalLight() {};
	DirectinalLight(glm::vec3 dir) : direction(dir) {};
	glm::vec3 direction = glm::vec3(0.0);
};