#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

class Box : public GameObject
{
public:
	Box(glm::vec3 color = glm::vec3(0.2));
	void draw(RenderData& renderData) override;
	Mesh mesh;
private:
	ShaderProgram shader;
};
