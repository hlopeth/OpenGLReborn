#include "UIRect.h"
#include "WindowManager.h"
#include "Trace.h"

using namespace UI;
GLuint UIRect::VAO = 0;

void initializeVAO(GLuint* VAO)
{
	GLfloat vertices[] = {
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f
	};
	GLuint indices[] = { 0, 1, 2, 0, 2, 3 };

	GLuint VBO;
	GLuint EBO;

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLfloat), indices, GL_STATIC_DRAW);
}

UIRect::UIRect()
{
	color = vec4(0.f);
	shader = ShaderProgram("UIRectVertex.glsl", "UIRectFragment.glsl");
	if (VAO == 0)
	{
		initializeVAO(&VAO);
	}
}

UIRect::UIRect(vec4 _color): UIRect()
{
	color = _color;
}

UIRect::~UIRect()
{
}

int UI::UIRect::getMaxChildren()
{
	return 0;
}

void onMouseMove()
{

}

void UI::UIRect::call(UIEvent& event)
{
	UIWiget::call(event);

	if (globalTransform.hasPoint(event.x, event.y))
	{
		switch (event.getType())
		{
		case MOUSE_CLICK_LEFT:
			color = vec4(1.0);
			break;
		default:
			break;
		}
	}
}

void UIRect::draw(const Rect& renderArea)
{
	shader.use();
	vec4 u_transform = vec4(
		globalTransform.x,
		globalTransform.y,
		globalTransform.width,
		globalTransform.height
	);
	shader.setUniform("u_transform", u_transform);
	shader.setUniform("u_viewportSize", vec2(WindowManager().windowWidth, WindowManager().windowHeight));
	shader.setUniform("u_color", color);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}