#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include "Transform3DComponent.h"

class Physics
{
public:
	Physics();
	void update(double time, double deltaTime);
	btCollisionShape* createBoxShape(glm::vec3 size);
	void addRigitBody(btRigidBody* body);
	void removeRigidBody(btRigidBody* body);
	~Physics();
private:
	btVector3 tobtVector3(vec3 vector);
	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
};