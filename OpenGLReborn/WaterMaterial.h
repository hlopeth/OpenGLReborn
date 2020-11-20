#pragma once
#include "Model.h"
#include "Shader.h"

class WaterMaterial : public ModelMaterial
{
public:
	WaterMaterial(vec4 color);
	void draw(const Model& model, const RenderData& rd) const override;
	float time = 0;
private:
	vec4 color;
	ShaderProgram shader;
};