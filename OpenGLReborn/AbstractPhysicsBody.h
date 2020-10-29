#pragma once
#include "Physics.h"

class GameObject;

class AbstractPhysicsBody : public Transform3DComponent
{
public:
	AbstractPhysicsBody(GameObject& gameObject, float mass);
	virtual vec3 getPosition() const override;
	virtual vec3 getScale() const override;
	virtual vec3 getRotation() const override;
	virtual void setPosition(const vec3 position) override;
	virtual void setScale(const vec3 scale) override;
	virtual void setRotation(const vec3 rotation) override;
	GameObject& gameObject() const;
	float mass() const;
	void setMass(float mass);
	~AbstractPhysicsBody();
protected:
	void initRigitBody(btCollisionShape* shape);
	
	GameObject& _gameObject;
	float _mass = 0.f;
	btRigidBody* _rigitBody;
};