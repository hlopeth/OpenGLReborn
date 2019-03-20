#pragma once
#include "Model.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Actor
{
public:
	Model model;
	ShaderProgram shader;
	glm::mat4 matrix;

	Actor(Model model, ShaderProgram shader, glm::mat4 matrix)
	{
		this->model = model;
		this->shader = shader;
		this->matrix = matrix;
	}

	void Draw(glm::mat4 ViewProj)
	{
		shader.setUniform("mvp", ViewProj*matrix);
		shader.setUniform("model", matrix);
		model.Draw(shader);
	}

	void Draw(glm::mat4 ViewProj, ShaderProgram override_shader)
	{
		shader.setUniform("mvp", ViewProj*matrix);
		shader.setUniform("model", matrix);
		model.Draw(override_shader);
	}
};
