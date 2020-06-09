#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

class Plane: public GameObject {
public:
	Plane(glm::vec3 color = glm::vec3(1.0));
	void draw(RenderData& renderData) override;
	Mesh mesh;
private:
	ShaderProgram shader;
};