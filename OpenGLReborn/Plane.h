#pragma once
#include "GameObject.h"
#include "Shader.h"

class Plane: public GameObject {
public:
	Plane();
	void draw(RenderData& renderData) override;
private:
	GLuint vao;
	ShaderProgram shader;
	GLsizei indices_count;
};