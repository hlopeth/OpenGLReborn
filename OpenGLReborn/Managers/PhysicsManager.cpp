#include "PhysicsManager.h"

Physics* PhysicsManager::physics = nullptr;

void PhysicsManager::initialise()
{
	physics = new Physics();
}

void PhysicsManager::destroy()
{
	delete physics;
	physics = nullptr;
}

Physics& PhysicsManager::getPhysics()
{
	return *physics;
}