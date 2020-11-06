#include "HeightfieldPhysicsBody.h"

HeightfieldPhysicsBody::HeightfieldPhysicsBody(
	int width,
	int height,
	float* data,
	float minHeight,
	float maxHeight,
	GameObject& gameObject, 
	float mass
): AbstractPhysicsBody(gameObject, mass)
{
	heightFieldShape = new btHeightfieldTerrainShape(
		width,
		height,
		data,
		btScalar(1),
		btScalar(minHeight),
		btScalar(maxHeight),
		1, // Y is up axis
		PHY_FLOAT,
		false
	);
	initRigitBody(heightFieldShape);
}

HeightfieldPhysicsBody::HeightfieldPhysicsBody(Texture heightmap, GameObject& gameObject, float mass):
	AbstractPhysicsBody(gameObject, mass)
{
	auto texWidth = heightmap.width;
	auto texHeight = heightmap.height;
	heights = std::make_unique<float*>(new float[texWidth * texHeight]);

	float maxHeight = heightmap.data[0];
	float minHeight = heightmap.data[0];

	int i = 0;
	for (int x = 0; x < texWidth; x++) {
		for (int y = 0; y < texHeight; y++) {
			float height = heightmap.data[(y * texHeight + x)];
			maxHeight = height > maxHeight? height: maxHeight;
			minHeight = height < minHeight ? height : minHeight;
			(*heights)[i++] = height;
		}
	}

	heightFieldShape = new btHeightfieldTerrainShape(
		texWidth,
		texHeight,
		*heights,
		btScalar(1),
		btScalar(minHeight),
		btScalar(maxHeight),
		1, // Y is up axis
		PHY_FLOAT,
		false
	);
	initRigitBody(heightFieldShape);
}
