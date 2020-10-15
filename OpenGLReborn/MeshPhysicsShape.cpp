#include "MeshPhysicsShape.h"
#include <bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleMesh.h>

MeshPhysicsShape::MeshPhysicsShape(GameObject& gameObject, float mass, Mesh* _mesh):
	AbstractPhysicsBody(gameObject, mass, getConvexHullShape(_mesh)),
	mesh(_mesh)
{
}

btCollisionShape* MeshPhysicsShape::getConvexHullShape(Mesh* _mesh)
{
	this->mesh = _mesh;
	return createCollisionShape();
}

btCollisionShape* MeshPhysicsShape::createCollisionShape()
{
	btConvexHullShape* shape = new btConvexHullShape();
	for (int i = 0; i < mesh->vertices.size(); i++)
	{
		vec3 pos = mesh->vertices[i].Position;
		shape->addPoint(btVector3(pos.x, pos.y, pos.z), i == mesh->vertices.size() - 1);
	}
	return shape;
}