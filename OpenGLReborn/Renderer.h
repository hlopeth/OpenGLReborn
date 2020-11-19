#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include "AbstractRenderer.h"
#include "ResizeEvent.h"
#include "Shader.h"

class Renderer : public AbstractRenderer
{
public:
	Renderer(GLFWwindow& window);
	~Renderer();
	virtual void draw(Level& level) override;
	void resize(const ResizeEvent& event);

	static const int glMajorVersion = 4;
	static const int glMinorVersion = 4;
private:
	GLFWwindow& window;
	int viewportWidth = 0;
	int viewportHeight = 0;
	ShaderProgram outlineShader;
};