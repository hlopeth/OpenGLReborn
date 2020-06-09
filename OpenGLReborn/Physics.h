#pragma once
#include <bullet/btBulletDynamicsCommon.h>

class Physics
{
public:
	Physics();
	void update(double time, double deltaTime);
	void addRigidBody(btRigidBody& body);
	~Physics();
private:
	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
};