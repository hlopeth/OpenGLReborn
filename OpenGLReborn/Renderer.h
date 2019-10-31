#pragma once
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "ResizeEvent.h"
#include "EventHandler.h"

class Renderer : EventHandler
{
public:
	Renderer(GLFWwindow& window);
	~Renderer();
	void draw(Scene& scene);
	void call(Event& event) override;

	static const int glMajorVersion = 4;
	static const int glMinorVersion = 4;
	const int screenWidth = 1920;
	const int screenHeight = 1080;
private:
	const GLFWwindow& window;
};