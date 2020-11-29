#include "BoxPhysicsShape.h"

BoxPhysicsShape::BoxPhysicsShape(vec3 size, GameObject& gameObject, float mass):
	AbstractPhysicsBody(gameObject, mass)
{
	boxShape = new btBoxShape(btVector3(size.x, size.y, size.z));
	initRigitBody(boxShape);
}