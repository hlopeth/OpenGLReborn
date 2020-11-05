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
		glm::vec3 color,
		bool _useSpecular
	);
	virtual void draw(Model& model, const RenderData& renderData) override;
private:
	GLTexture diffuseTexture;
	GLTexture specularTexture;
	GLTexture normalTexture;
	glm::vec3 color;
	bool useSpecular;
	ShaderProgram shaderProgram;
};