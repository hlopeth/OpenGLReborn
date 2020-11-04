#pragma once
#include "Model.h"
#include "GLTexture.h"
#include "Shader.h"

class NanosuitMaterial : public ModelMaterial
{
public:
	NanosuitMaterial(
		GLTexture diffuseTexture,
		GLTexture specularTexture,
		GLTexture normalTexture,
		glm::vec3 color
	);
	virtual void draw(Model& model, const RenderData& renderData) override;
private:
	GLTexture diffuseTexture;
	GLTexture specularTexture;
	GLTexture normalTexture;
	glm::vec3 color;
	ShaderProgram shaderProgram;
};