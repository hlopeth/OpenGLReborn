#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Level.h"
#include "ResizeEvent.h"
#include "EventHandler.h"

class Renderer : EventHandler
{
public:
	Renderer(GLFWwindow& window);
	~Renderer();
	void draw(Level& level);
	void call(Event& event) override;

	static const int glMajorVersion = 4;
	static const int glMinorVersion = 4;
private:
	GLFWwindow& window;
	int viewportWidth = 0;
	int viewportHeight = 0;
};