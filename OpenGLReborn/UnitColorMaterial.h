#pragma once
#include "Model.h"

class UnitColorMaterial : public ModelMaterial
{
public:
	UnitColorMaterial(glm::vec3 color);
	virtual void draw(Model& model, const RenderData& rd) override;
	glm::vec3 color;
private: 
	ShaderProgram shaderProgram;
};