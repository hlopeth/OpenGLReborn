#pragma once
#include "Transform3DComponent.h"
#include "DrawComponent.h"
#include "EventComponent.h"
#include "AbstractPhysicsBody.h"

using glm::mat4;

class GameObject: 
	public Transform3DComponent, 
	public DrawComponent, 
	public EventComponent
{
public:
	GameObject();
	vec3 getPosition() const override;
	vec3 getScale() const override;
	vec3 getRotation() const override;
	virtual void setPosition(const vec3 position) override;
	void setScale(const vec3 scale) override;
	void setRotation(const vec3 rotation) override;
	void call(const Event& event) override;
	virtual void afterPhysicsUpdate();
	void addChild(GameObject* child);
	virtual void update(double gameTime, double deltaTime);
	virtual void draw(RenderData& renderData) = 0;
	bool usePhysics();
	mat4 getModelMatrix();
	~GameObject();

	AbstractPhysicsBody* physicsBody = nullptr;
	bool selectable = false;
protected:
	GameObject* parent = nullptr;
	vector<GameObject*> childs;
private:
	vec3 position;
	vec3 scale;
	vec3 rotation;
	mat4 modelMatrix;
	bool modelMatrixIsDirty = true;
};