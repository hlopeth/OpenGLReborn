#pragma once
#include "Components/Transform3DComponent.h"
#include "Components/DrawComponent.h"
#include "Components/EventComponent.h"
#include "Physics/AbstractPhysicsBody.h"

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
	virtual void draw(RenderData& renderData) const = 0;
	bool usePhysics();
	const mat4 getModelMatrix() const;
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
	mutable mat4 modelMatrix;
	mutable bool modelMatrixIsDirty = true;
};