#include "WindowManager.h"
#include "RendererManager.h"
#include "InputManager.h"
#include "InitialisationExeption.h"
#include "Trace.h"

bool initialiseManagers();
void destroyManagers();
void startGameLoop();

int main()
{
	initialiseManagers();

	startGameLoop();
	
	destroyManagers();
	return 0;
}

bool initialiseManagers()
{
	try
	{
		WindowManager().initialise();
		InpuManager().initialise();
		RendererManager().initialise();
	}
	catch (InitialisationExeption ex)
	{
		trace(ex.getMessage());
		return false;
	}
	return true;
}

void destroyManagers()
{
	InpuManager().destroy();
	RendererManager().destroy();
	WindowManager().destroy();
}

void startGameLoop()
{
	GLFWwindow& window = WindowManager().getWindow();
	while (!glfwWindowShouldClose(&window))
	{
		glfwPollEvents();
	}
}