#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
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
	ShaderProgram(string vertexShaderFileName, string fragmentShaderFileName, string geomertyShaderFileName = "")
	{
		id = createShaderProgram(vertexShaderFileName, fragmentShaderFileName, geomertyShaderFileName);
	}
	void use() const;
	void setUniform(string name, unsigned int val) const
	{
		glUniform1ui(findLocation(name), val);
	}
	void setUniform(string name, int val) const
	{
		glUniform1i(findLocation(name), val);
	}
	void setUniform(string name, float val) const
	{
		glUniform1f(findLocation(name), val);
	}
	void setUniform(string name, glm::mat4 val) const
	{
		glUniformMatrix4fv(findLocation(name), 1, GL_FALSE, glm::value_ptr(val));
	}
	void setUniform(string name, glm::vec2 val) const
	{
		glUniform2fv(findLocation(name), 1, glm::value_ptr(val));
	}
	void setUniform(string name, glm::vec3 val) const
	{
		glUniform3fv(findLocation(name),1, glm::value_ptr(val));
	}
	void setUniform(string name, glm::vec4 val) const
	{
		glUniform4fv(findLocation(name), 1, glm::value_ptr(val));
	}
private:
	GLuint createShaderProgram(string vertexShaderFileName, string fragmentShaderFileName, string geomertyShaderFileName = "");
	GLuint compileShader(const string source, GLenum type);
	string getSource(string fileName);
	GLint findLocation(const string& name) const;
};
