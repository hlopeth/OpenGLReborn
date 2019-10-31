#pragma once
#include <GLFW/glfw3.h>

class Input
{
public:
	Input(GLFWwindow& window);

private:
	void addCallbacks(GLFWwindow* window);
};