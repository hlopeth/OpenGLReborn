#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Level.h"
#include "ResizeEvent.h"
#include "EventComponent.h"

class Renderer : public EventComponent
{
public:
	Renderer(GLFWwindow& window);
	~Renderer();
	void draw(Level& level);
	void resize(const ResizeEvent& event);

	static const int glMajorVersion = 4;
	static const int glMinorVersion = 4;
private:
	GLFWwindow& window;
	int viewportWidth = 0;
	int viewportHeight = 0;
};