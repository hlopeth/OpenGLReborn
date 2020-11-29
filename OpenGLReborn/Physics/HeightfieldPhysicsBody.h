#pragma once
#include <memory>
#include "Physics/AbstractPhysicsBody.h"
#include "Texture.h"
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>

class HeightfieldPhysicsBody : public AbstractPhysicsBody
{
public:
	HeightfieldPhysicsBody(
		int width,
		int height,
		float* data,
		float minHeight,
		float maxHeight,
		GameObject& gameObject,
		float mass
	);
	HeightfieldPhysicsBody(Texture heightmap, GameObject& gameObject, float mass);
private:
	btHeightfieldTerrainShape *heightFieldShape;
	std::unique_ptr<float*> heights;
};
