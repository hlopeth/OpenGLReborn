#pragma once
#include "Model.h"
#include "Shader.h"
#include "GLTexture.h"

class TerrainMaterial : public ModelMaterial 
{
public:
	TerrainMaterial(GLTexture diffuseTexture);
	virtual void draw(Model& model, const RenderData& renderData) override;
private:
	GLTexture diffuseTexture;
	ShaderProgram shader;
};