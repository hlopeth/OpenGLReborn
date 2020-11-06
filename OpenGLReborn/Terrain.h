#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include <glm\detail\type_float.hpp>

class Terrain : public Model {
public:
	Terrain(Texture heightMap, GLTexture texture);
	float lowestPoint = 0.0f;
	float hightestPoint = 0.0f;
private:
	Mesh generateMesh(Texture heightmap);
};