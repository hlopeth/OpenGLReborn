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
	Mesh& getMesh();
private:
	Mesh* mesh;
	Mesh* generateMesh(Texture heightmap, GLTexture texture);
	ShaderProgram shader;
};