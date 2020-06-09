#include "Plane.h"

Plane::Plane()
{
	GLfloat vertices[] = {
		//pos______________   tex_coord_   normal____________
		-1.0f,  0.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  0.0f, -1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  0.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 1.0f,  0.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  0.0f,  1.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  0.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	};

	GLuint indices[] = {
		0, 1, 2, 3, 4, 5
	};

	indices_count = 6;
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

	shader = ShaderProgram("DefaultVertex.glsl", "DefaultFragment.glsl");
}

void Plane::draw(RenderData& renderData)
{
	shader.use();
	auto model = getModelMatrix();
	auto mvp = renderData.camera.getViewProjection() * model;
	shader.setUniform("model", model);
	shader.setUniform("mvp", mvp);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, indices_count);
}
