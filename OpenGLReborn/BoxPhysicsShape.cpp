#include "BoxPhysicsShape.h"

BoxPhysicsShape::BoxPhysicsShape(GameObject& gameObject, float mass):
	AbstractPhysicsBody(gameObject, mass, createCollisionShape())
{
}

btCollisionShape* BoxPhysicsShape::createCollisionShape()
{
	return new btBoxShape(btVector3(1.f, 1.f, 1.f));
}