#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "Material.h"

class Model
{
public:
	GLuint VAO;
	ShaderProgram shaderProgram;
	vector<GLuint> textures;
	GLint n;
	Material material;
	bool useMaterial;
	bool useTexture;

	Model(GLuint VAO, ShaderProgram shaderProgram, GLint n)
	{
		this->VAO = VAO;
		this->shaderProgram = shaderProgram;
		this->n = n;
		useMaterial = false;
		useTexture = false;
	}

	Model(GLuint VAO, ShaderProgram shaderProgram, GLint n, Material material)
	{
		this->VAO = VAO;
		this->shaderProgram = shaderProgram;
		this->n = n;
		this->material = material;
		useMaterial = true;
		useTexture = false;
	}

	Model(GLuint VAO, ShaderProgram shaderProgram, GLint n, vector<GLuint> textures)
	{
		this->VAO = VAO;
		this->shaderProgram = shaderProgram;
		this->n = n;
		this->textures = textures;
		useMaterial = false;
		useTexture = true;
	}

	Model(GLuint VAO, ShaderProgram shaderProgram, GLint n, vector<GLuint> textures, Material material)
	{
		this->VAO = VAO;
		this->shaderProgram = shaderProgram;
		this->textures = textures;
		this->n = n;
		this->material = material;
		useMaterial = true;
		useTexture = true;
	};
	void use()
	{
		shaderProgram.use();
		glBindVertexArray(VAO);
		if(useTexture)
			for (int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textures[i]);
			}
		if (useMaterial)
		{
			shaderProgram.setUniform("material.ambient",  material.ambient);
			shaderProgram.setUniform("material.diffuse",  material.diffuse);
			shaderProgram.setUniform("material.specular", material.specular);
			shaderProgram.setUniform("material.shininess", material.shininess);
		}
	}
	void draw()
	{
		glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, 0);
	}
};