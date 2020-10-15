#pragma once
#include "AbstractPhysicsBody.h"
#include "Mesh.h"

class MeshPhysicsShape : public AbstractPhysicsBody
{
public:
	MeshPhysicsShape(GameObject& gameObject, float mass, Mesh* mesh);
private:
	Mesh* mesh;
	btCollisionShape* getConvexHullShape(Mesh* mesh);
	virtual btCollisionShape* createCollisionShape() override;
};