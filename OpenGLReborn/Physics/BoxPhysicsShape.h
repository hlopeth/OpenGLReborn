#pragma once
#include "AbstractPhysicsBody.h"

class BoxPhysicsShape : public AbstractPhysicsBody
{
public:
	BoxPhysicsShape(vec3 size, GameObject& gameObject, float mass);
private:
	btBoxShape* boxShape;
};