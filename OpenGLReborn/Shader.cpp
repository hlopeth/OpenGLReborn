#include "Shader.h"

GLuint ShaderProgram::createShaderProgram(string vertexShaderFileName, string fragmentShaderFileName)
{
	GLuint shaderProgram = glCreateProgram();

	string vertexSource = getSource(vertexShaderFileName);
	string fragmentSource = getSource(fragmentShaderFileName);

	GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);


	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	GLint success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

GLuint ShaderProgram::compileShader(const string source, GLenum type)
{
	GLuint shader = glCreateShader(type);

	const GLchar* c_source = source.c_str();
	glShaderSource(shader, 1, &c_source, NULL);
	glCompileShader(shader);

	GLint success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

string ShaderProgram::getSource(string fileName)
{
	string shaderSource = "";
	try
	{
		ifstream source_file;
		source_file.open(fileName);
		std::stringstream shaderStream;
		shaderStream << source_file.rdbuf();
		source_file.close();
		shaderSource = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderSource;
}

void ShaderProgram::use()
{
	glUseProgram(id);
}