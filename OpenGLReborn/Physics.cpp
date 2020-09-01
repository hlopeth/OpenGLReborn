#include "Physics.h"
#include "LevelManager.h"

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
	LEVEL.onPhysicsUpdate();
}

void Physics::addRigitBody(btRigidBody* body)
{
	dynamicsWorld->addRigidBody(body);
}

btCollisionShape* Physics::createBoxShape(glm::vec3 size)
{
	auto box = new btBoxShape(btVector3(btScalar(size.x), btScalar(size.y), btScalar(size.z)));
	return box;
}

void Physics::removeRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeRigidBody(body);
	body = nullptr;
}

btVector3 Physics::tobtVector3(vec3 vector)
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