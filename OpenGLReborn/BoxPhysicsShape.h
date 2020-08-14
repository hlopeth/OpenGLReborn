#pragma once
#include "AbstractPhysicsBody.h"

class BoxPhysicsShape : public AbstractPhysicsBody
{
public:
	BoxPhysicsShape(GameObject& gameObject, float mass);
protected:
	virtual btCollisionShape* createCollisionShape() override;
};