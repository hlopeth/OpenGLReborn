#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ShaderProgram
{
public:
	GLuint id;
	ShaderProgram()
	{
		id = -1;
	}
	ShaderProgram(string vertexShaderFileName, string fragmentShaderFileName)
	{
		id = createShaderProgram(vertexShaderFileName, fragmentShaderFileName);
	}
	void use();
	void setUniform(string name, unsigned int val)
	{
		glUniform1ui(glGetUniformLocation(id, name.c_str()), val);
	}
	void setUniform(string name, int val)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), val);
	}
	void setUniform(string name, float val)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), val);
	}
	void setUniform(string name, glm::mat4 val)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
	}
	void setUniform(string name, glm::vec3 val)
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()),1, glm::value_ptr(val));
	}
private:
	GLuint createShaderProgram(string vertexShaderFileName, string fragmentShaderFileName);
	GLuint compileShader(const string source, GLenum type);
	string getSource(string fileName);
};
