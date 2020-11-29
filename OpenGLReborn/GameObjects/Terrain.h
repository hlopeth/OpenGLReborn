#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Material/TerrainMaterial.h"

struct TerrainVertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV1;
	glm::vec3 Alphas;
};

class Terrain : public GameObject {
public:
	Terrain(Texture heightMap, shared_ptr<TerrainMaterial> material);
	void draw(RenderData& renderData) const override;
	float getLowestPoint() const;
	float getHightestPoint() const;
private:
	float lowestPoint = 0.0f;
	float hightestPoint = 0.0f;
	bool shouldUpload = true;
	GLuint VAO;
	void generateMesh(Texture heightmap);
	void upload();
	std::vector<TerrainVertex> vertices;
	std::vector<uint32_t> indices;
	shared_ptr<TerrainMaterial> material;
};