#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include <glm\detail\type_float.hpp>

class Terrain : public Model {
public:
	Terrain(Texture heightMap, GLTexture texture);
	~Terrain();
	Mesh& getMesh();
private:
	Mesh* mesh;
	Mesh generateMesh(Texture heightmap);
	ShaderProgram shader;
};