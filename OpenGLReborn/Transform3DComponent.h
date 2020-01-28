#pragma once
#include <glm/glm.hpp>

using glm::vec3;

class Transform3DComponent
{
public:
	virtual vec3 getPosition() = 0;
	virtual vec3 getScale() = 0;
	virtual vec3 getRotation() = 0;
	virtual void setPosition(const vec3 position) = 0;
	virtual void setScale(const vec3 scale) = 0;
	virtual void setRotation(const vec3 rotation) = 0;
};