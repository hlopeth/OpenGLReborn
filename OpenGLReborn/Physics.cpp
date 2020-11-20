#include "Physics.h"
#include "LevelManager.h"
#include <bullet/btBulletCollisionCommon.h>

Physics::Physics()
{
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	///-----initialization_end-----
}

void Physics::update(double time, double deltaTime)
{
	dynamicsWorld->stepSimulation(deltaTime);

	LEVEL.afterPhysicsUpdate();
}

void Physics::addRigitBody(btRigidBody* rigitBody, AbstractPhysicsBody* abstractPhysicsBody)
{
	rigitBodyToAbstactPhysicsBody[rigitBody] = abstractPhysicsBody;
	dynamicsWorld->addRigidBody(rigitBody);
}

btCollisionShape* Physics::createBoxShape(glm::vec3 size)
{
	auto box = new btBoxShape(btVector3(btScalar(size.x), btScalar(size.y), btScalar(size.z)));
	return box;
}

void Physics::removeRigidBody(btRigidBody* body)
{
	rigitBodyToAbstactPhysicsBody[body] = nullptr;
	dynamicsWorld->removeRigidBody(body);
	body = nullptr;
}

bool Physics::rayCast(const vec3& _from, const vec3& _to, vec3& oHitPoint, vec3& oHitNormal, AbstractPhysicsBody* &outBody)
{
	btVector3 from = to_btVector3(_from);
	btVector3 to = to_btVector3(_to);
	btCollisionWorld::ClosestRayResultCallback rayCallback(from, to);

	dynamicsWorld->rayTest(from, to, rayCallback);
	if (rayCallback.hasHit()) 
	{
		oHitPoint = to_vec3(rayCallback.m_hitPointWorld);
		oHitNormal = to_vec3(rayCallback.m_hitNormalWorld);
		auto abstractPhysicsBody = rigitBodyToAbstactPhysicsBody.find((btRigidBody*)rayCallback.m_collisionObject);
		if (abstractPhysicsBody != rigitBodyToAbstactPhysicsBody.end()) 
		{
			outBody = abstractPhysicsBody->second;
		}
		else
		{
			outBody = nullptr;
		}
		return true;
	}
	return false;
}

vec3 Physics::to_vec3(btVector3 vector)
{
	return vec3(vector.x(), vector.y(), vector.z());
}

btVector3 Physics::to_btVector3(vec3 vector)
{
	return btVector3(btScalar(vector.x), btScalar(vector.y), btScalar(vector.z));
}

Physics::~Physics()
{ 
	//remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfiguration;
}