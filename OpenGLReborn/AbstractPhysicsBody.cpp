#include "AbstractPhysicsBody.h"
#include "InitialisationExeption.h"
#include "PhysicsManager.h"
#include "GameObject.h"

AbstractPhysicsBody::AbstractPhysicsBody(
	GameObject& gameObject, 
	float mass):
	_mass(mass),
	_gameObject(gameObject)
{
}

void AbstractPhysicsBody::initRigitBody(btCollisionShape* collisionShape)
{
	bool isDynamic = _mass != 0;
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
	{
		collisionShape->calculateLocalInertia(_mass, localInertia);
	}
	_rigitBody = new btRigidBody(_mass, 0, collisionShape, localInertia);
	copyTransform(_gameObject);
	PHYSICS.addRigitBody(_rigitBody);
}

vec3 AbstractPhysicsBody::getPosition() const
{
	btVector3 origin = _rigitBody->getWorldTransform().getOrigin();
	return vec3(origin.x(), origin.y(), origin.z());
}

vec3 AbstractPhysicsBody::getScale() const
{
	btVector3 scale = _rigitBody->getCollisionShape()->getLocalScaling();
	return vec3(scale.x(), scale.y(), scale.z());
}

vec3 AbstractPhysicsBody::getRotation() const
{
	btQuaternion rot = _rigitBody->getWorldTransform().getRotation();
	btScalar x, y, z;
	rot.getEulerZYX(z, y, x);
	return vec3((float)x, (float)y, (float)z);
}

void AbstractPhysicsBody::setPosition(const vec3 position)
{
	btVector3 origin = btVector3(
		btScalar(position.x),
		btScalar(position.y),
		btScalar(position.z)
	);
	_rigitBody->getWorldTransform().setOrigin(origin);
}

void AbstractPhysicsBody::setScale(const vec3 scale)
{
	btVector3 localScaling = btVector3(
		btScalar(scale.x),
		btScalar(scale.y),
		btScalar(scale.z)
	);
	_rigitBody->getCollisionShape()->setLocalScaling(localScaling);
}

void AbstractPhysicsBody::setRotation(const vec3 rotation)
{
	btQuaternion btRotation;
	btRotation.setEulerZYX(
		btScalar(rotation.z),
		btScalar(rotation.y),
		btScalar(rotation.x)
	);
	_rigitBody->getWorldTransform().setRotation(btRotation);
}

GameObject& AbstractPhysicsBody::gameObject() const
{
	return _gameObject;
}

float AbstractPhysicsBody::mass() const
{
	return (float) _rigitBody->getMass();
}

void AbstractPhysicsBody::setMass(float mass)
{
	bool isDynamic = mass != 0;

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
	{
		_rigitBody->getCollisionShape()->calculateLocalInertia(mass, localInertia);
	}
	_rigitBody->setMassProps(btScalar(mass), localInertia);
}

AbstractPhysicsBody::~AbstractPhysicsBody()
{
	PHYSICS.removeRigidBody(_rigitBody);
}

