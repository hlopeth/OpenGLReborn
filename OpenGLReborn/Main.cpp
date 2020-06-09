#include "WindowManager.h"
#include "RendererManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "PhysicsManager.h"
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
		InputManager().initialise();
		RendererManager().initialise();
		PhysicsManager().initialise();
		LevelManager().initialize();
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
	LevelManager().destroy();
	InputManager().destroy();
	RendererManager().destroy();
	WindowManager().destroy();
	PhysicsManager().destroy();
}

void startGameLoop()
{
	while (!glfwWindowShouldClose(&WINDOW))
	{
		INPUT.pullEvents();
		LEVEL.update();
		RENDERER.draw(LEVEL);
	}
}