#pragma once
#include "GameObjects/Model.h"
#include "GLTexture.h"
#include "Shader.h"

class SingleTextureMaterial : public ModelMaterial
{
public:
	SingleTextureMaterial(GLTexture diffuseTexture, glm::vec3 color = glm::vec3(0.0));
	virtual void draw(const Model& model, const RenderData& renderData) const override;
	GLTexture diffuseTexture;
	glm::vec3 color;
private:
	ShaderProgram shader;
};