#pragma once
#include "GameObject.h"
#include "Shader.h"
#include <glad/glad.h>

class Triangle : public GameObject
{
public:
	Triangle();
	~Triangle();
	void draw(Camera& camera) override;
private:
	ShaderProgram shaderProgram;
	GLuint VBO;
	GLuint VAO;
};