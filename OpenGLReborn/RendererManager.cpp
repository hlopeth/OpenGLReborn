#include "RendererManager.h"
#include "WindowManager.h"
#include "InitialisationExeption.h"
#include "Renderer.h"
#include "StereoRenderer.h"

AbstractRenderer* RendererManager::renderer = nullptr;

void RendererManager::initialise()
{
	GLFWwindow& window = WindowManager().getWindow();
	glfwMakeContextCurrent(&window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		renderer = nullptr;
		throw InitialisationExeption("Failed to initialize GLAD");
	}
	renderer = new StereoRenderer(window);
}

void RendererManager::destroy()
{
	delete(renderer);
	renderer = nullptr;
}

AbstractRenderer& RendererManager::getRenderer()
{
	return *renderer;
}


