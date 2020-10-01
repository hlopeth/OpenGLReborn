#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "Texture.h"
#include <glm\detail\type_float.hpp>

class Terrain : public GameObject {
public:
	Terrain(Texture heightMap, GLTexture texture);
	void draw(RenderData& renderData) override;
	~Terrain();
	float getLowestPoint() const;
	float getHightestPoint() const;
private:
	Mesh* mesh;
	Mesh* generateMesh(Texture heightmap, GLTexture texture);
	ShaderProgram shader;
	float lowestPoint = 9999999999.0;
	float hightestPoint = -999999999.0;
};