#pragma once
#include "GameObjects/Model.h"
#include "Shader.h"
#include "GLTexture.h"

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
