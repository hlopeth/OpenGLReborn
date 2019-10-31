#include "WindowManager.h"
#include "InitialisationExeption.h"
#include "Renderer.h"

GLFWwindow* WindowManager::window = nullptr;

void WindowManager::initialise()
{
	if (!glfwInit())
	{
		throw InitialisationExeption("Failed to init GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Renderer::glMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Renderer::glMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//buff for antyaliasing MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Reborn", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		window = nullptr;
		throw InitialisationExeption("Failed to create GLFW window");
	}
}

void WindowManager::destroy()
{
	glfwTerminate();
	window = nullptr;
}

GLFWwindow& WindowManager::getWindow()
{
	return *window;
}
