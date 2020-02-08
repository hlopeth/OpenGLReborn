#include "Box.h"

Box::Box()
{
	GLfloat vertices[] = {
		//pos______________   tex_coord_   normal____________
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	};
	GLuint indices[] = {
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36 
	};
	indices_count = 36;
	GLuint vbo = 0, ebo = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	shader = ShaderProgram("BoxVertex.glsl", "BoxFragment.glsl");
}

void Box::draw(RenderData& renderData)
{
	shader.use();
	auto model = getModelMatrix();
	auto mvp = renderData.camera.getViewProjection() * model;
	shader.setUniform("model", model);
	shader.setUniform("mvp", mvp);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, indices_count);
}
