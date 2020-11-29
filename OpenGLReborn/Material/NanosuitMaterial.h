#pragma once
#include "GameObjects/Model.h"
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
	virtual void draw(const Model& model, const RenderData& renderData) const override;
private:
	GLTexture diffuseTexture;
	GLTexture specularTexture;
	GLTexture normalTexture;
	glm::vec3 color;
	bool useSpecular;
	ShaderProgram shaderProgram;
};