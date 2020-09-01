#pragma once
#include <GLFW/glfw3.h>

class Input
{
public:
	Input(GLFWwindow& window);
	void pullEvents();
	static float sensitivity;
private:
	void addCallbacks(GLFWwindow* window);
};