#pragma once
#include "AbstractMaterial.h"
#include "Shader.h"
#include "GLTexture.h"
#include "RenderData.h"

class TerrainMaterial : public AbstractMaterial
{
public:
	TerrainMaterial(GLTexture sandTexture, GLTexture grassTexture, GLTexture rockTexture);
	void draw(GLuint vao, int indicesSize, const glm::mat4& modelMatrix, const RenderData& renderData);
private:
	GLTexture sandTexture;
	GLTexture grassTexture;
	GLTexture rockTexture;
	ShaderProgram shader;
};