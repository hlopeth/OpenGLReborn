#pragma once
#include <GLFW/glfw3.h>

#ifndef WINDOW
#define WINDOW WindowManager().getWindow()
#endif // !WINDOW


class WindowManager
{
public:
	void initialise();
	void destroy();
	GLFWwindow& getWindow();

	static const int windowWidth = 200;
	static const int windowHeight = 300;
private:
	static GLFWwindow* window;
};