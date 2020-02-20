#pragma once
#include "Transform3DComponent.h"
#include "DrawComponent.h"
#include "EventComponent.h"

using glm::mat4;

class GameObject: public Transform3DComponent, public DrawComponent, public EventComponent
{
public:
	GameObject();
	vec3 getPosition() override;
	vec3 getScale() override;
	vec3 getRotation() override;
	virtual void setPosition(const vec3 position) override;
	void setScale(const vec3 scale) override;
	void setRotation(const vec3 rotation) override;
	void call(const Event& event) override;
	void addChild(GameObject* child);
	virtual void draw(RenderData& renderData) = 0;
protected:
	mat4 getModelMatrix();
	GameObject* parent = nullptr;
	vector<GameObject*> childs;
private:
	vec3 position;
	vec3 scale;
	vec3 rotation;
	mat4 modelMatrix;
	bool modelMatrixIsDirty = true;
};