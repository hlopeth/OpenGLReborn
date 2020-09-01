#include "Input.h"
#include "RendererManager.h"
#include "ResizeEvent.h"
#include "MouseMoveEvent.h"
#include "KeyEvent.h"
#include "MouseClickEvent.h"
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
	KeyEvent ev = KeyEvent(key, action);
	LEVEL.call(ev);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= Input::sensitivity;
	yoffset *= Input::sensitivity;

	MouseMoveEvent ev = MouseMoveEvent(xpos, ypos, xoffset, yoffset);
	LEVEL.call(ev);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	bool pressed = action == GLFW_PRESS;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		MouseLeftClickEvent ev = MouseLeftClickEvent(lastX, lastY, pressed);
		LEVEL.call(ev);
		break;
	}
	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		MouseRightClickEvent ev = MouseRightClickEvent(lastX, lastY, pressed);
		LEVEL.call(ev);
		break;
	}
	default:
		break;
	}
}

void Input::addCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
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

