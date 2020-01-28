#pragma once
#include "Transform3DComponent.h"
#include "DrawComponent.h"

using glm::mat4;

class GameObject: Transform3DComponent, DrawComponent
{
public:
	GameObject();
	vec3 getPosition() override;
	vec3 getScale() override;
	vec3 getRotation() override;
	void setPosition(const vec3 position) override;
	void setScale(const vec3 scale) override;
	void setRotation(const vec3 rotation) override;
	virtual void draw(Camera& camera) = 0;
protected:
	mat4 getModelMatrix();
private:
	vec3 position;
	vec3 scale;
	vec3 rotation;
	mat4 modelMatrix;
};