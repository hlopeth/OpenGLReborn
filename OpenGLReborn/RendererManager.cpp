#include "RendererManager.h"
#include "WindowManager.h"
#include "InitialisationExeption.h"

Renderer* RendererManager::renderer = nullptr;

void RendererManager::initialise()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		renderer = nullptr;
		throw InitialisationExeption("Failed to initialize GLAD");
	}
	renderer = new Renderer(WindowManager().getWindow());
}

void RendererManager::destroy()
{
	renderer = nullptr;
}

Renderer& RendererManager::getRenderer()
{
	return *renderer;
}


