#pragma once
#include "Model.h"
#include "Shader.h"

class FullscreenTextureMaterial : public ModelMaterial
{
public:
	FullscreenTextureMaterial() = default;
	FullscreenTextureMaterial(GLTexture textureLeft, GLTexture textureRight);
	void draw(const Model& model, const RenderData& rd) const override;
	GLTexture textureLeft;
	GLTexture textureRight;
private:
	ShaderProgram shader;
};
