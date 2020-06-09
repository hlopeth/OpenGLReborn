#pragma once
#include "Physics.h"

#ifndef PHYSICS
#define PHYSICS PhysicsManager().getPhysics()
#endif // !PHYSICS


class PhysicsManager
{
public:
	void initialise();
	void destroy();
	Physics& getPhysics();
private:
	static Physics* physics;
};