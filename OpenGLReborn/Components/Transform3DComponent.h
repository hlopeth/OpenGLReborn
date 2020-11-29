#pragma once
#include <glm/glm.hpp>

using glm::vec3;

class Transform3DComponent
{
public:
	virtual vec3 getPosition() const = 0;
	virtual vec3 getScale() const = 0;
	virtual vec3 getRotation() const = 0;
	virtual void setPosition(const vec3 position) = 0;
	virtual void setScale(const vec3 scale) = 0;
	virtual void setRotation(const vec3 rotation) = 0;
	void copyTransform(const Transform3DComponent& transform);
};