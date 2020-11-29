#pragma once
#include <btBulletDynamicsCommon.h>
#include <map>
#include "Components/Transform3DComponent.h"

class AbstractPhysicsBody;

class Physics
{
public:
	Physics();
	void update(double time, double deltaTime);
	btCollisionShape* createBoxShape(glm::vec3 size);
	void addRigitBody(btRigidBody* body, AbstractPhysicsBody* abstractPhysicsBody);
	void removeRigidBody(btRigidBody* body);
	bool rayCast(const vec3& from, const vec3& to, vec3& oHitPoint, vec3& oHitNormal, AbstractPhysicsBody* &outBody);
	~Physics();
private:
	vec3 to_vec3(btVector3 vector);
	btVector3 to_btVector3(vec3 vector);
	btDiscreteDynamicsWorld* dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	std::map<btRigidBody*, AbstractPhysicsBody*> rigitBodyToAbstactPhysicsBody;
};