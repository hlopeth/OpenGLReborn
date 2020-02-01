#pragma once
#include "GameObject.h"
#include "Shader.h"

class Box : public GameObject
{
public:
	Box();
	void draw(RenderData& renderData) override;
private:
	GLuint vao;
	GLsizei indices_count;
	ShaderProgram shader;
};
