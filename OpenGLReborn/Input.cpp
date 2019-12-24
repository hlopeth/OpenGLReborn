#include "Input.h"
#include "RendererManager.h"
#include "ResizeEvent.h"
#include "MouseMoveEvent.h"
#include "LevelManager.h"

float lastX = 0;
float lastY = 0;
bool firstMouse = true;

float Input::sensitivity = 0.1f;

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
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= Input::sensitivity;
	yoffset *= Input::sensitivity;

	MouseMoveEvent ev = MouseMoveEvent(xpos, ypos, xoffset, yoffset);
	LEVEL.getCamera().call(ev);
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

