#pragma once
#include "Model.h"

class UnitColorMaterial : public ModelMaterial
{
public:
	UnitColorMaterial(glm::vec4 color);
	UnitColorMaterial(const UnitColorMaterial& material);
	virtual void draw(const Model& model, const RenderData& rd) const override;
	glm::vec4 color;
private: 
	ShaderProgram shaderProgram;
};