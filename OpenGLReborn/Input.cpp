#include "Input.h"
#include "RendererManager.h"
#include "ResizeEvent.h"

void resizeCallback(GLFWwindow* window, int width, int height)
{
	ResizeEvent ev = ResizeEvent(width, height);
	RendererManager().getRenderer().call(ev);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
}

void Input::addCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
}

Input::Input(GLFWwindow& window)
{
	//glfwSetInputMode(&window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	addCallbacks(&window);
}

void Input::pullEvents()
{
	glfwPollEvents();
}

