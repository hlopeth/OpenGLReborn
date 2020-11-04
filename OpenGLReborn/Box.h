#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Shader.h"
#include "BoxMaterial.h"

class Box : public Model
{
public:
	Box(glm::vec3 color = glm::vec3(0.2));
	shared_ptr<BoxMaterial> getMaterial() const;
private:
	ShaderProgram shader;
	shared_ptr<BoxMaterial> boxMaterial;
};
