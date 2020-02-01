#include "Triangle.h"
#include <glad/glad.h>
#include "Trace.h"


Triangle::Triangle()
{
	GLfloat vertices[] = {
		 0.5f, -0.5f,
		-0.5f, -0.5f,
		 0.0f,  0.5f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	
	shaderProgram = ShaderProgram("TriangleVertex.glsl", "TriangleFragment.glsl");
}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Triangle::draw(RenderData& renderData)
{
	shaderProgram.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
