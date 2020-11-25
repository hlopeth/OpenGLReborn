#include "WindowManager.h"
#include "InitializationException.h"
#include "Renderer.h"
#include "Trace.h"

GLFWwindow* WindowManager::window = nullptr;

void error_callback(int error, const char* description)
{
	string message = "GLAD ERROR " + std::to_string(error) + " : " + string(description);
	trace(message);
}

void WindowManager::initialise()
{
	if (!glfwInit())
	{
		throw InitializationException("Failed to init GLFW");
	}
	glfwSetErrorCallback(error_callback);

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
		throw InitializationException("Failed to create GLFW window");
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
