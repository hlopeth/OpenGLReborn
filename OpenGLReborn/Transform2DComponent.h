#pragma once
#include <glm/glm.hpp>

using glm::vec2;

class Transform2DComponent
{
public:
	virtual vec2 getPosition() = 0;
	virtual vec2 getSize() = 0;
	virtual void setPosition(const vec2 position) = 0;
	virtual void setSize(const vec2 size) = 0;
};