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
void updateTime(double& gameTime, double& deltaTime);

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
	double gameTime = 0;
	double deltaTime = 0;
	glfwSetTime(0);

	while (!glfwWindowShouldClose(&WINDOW))
	{
		updateTime(gameTime, deltaTime);
		INPUT.pullEvents();
		LEVEL.update(gameTime, deltaTime);
		PHYSICS.update(gameTime, deltaTime);
		RENDERER.draw(LEVEL);
	}
}

void updateTime(double& gameTime, double& deltaTime)
{
	double glfwTime = glfwGetTime();
	deltaTime = glfwTime - gameTime;

	//если прошло больше секунды с прошлого тика, то в этот тик время не идет.
	if (deltaTime > 1)
	{
		glfwSetTime(gameTime);
		deltaTime = 0;
	}
	else
	{
		gameTime = glfwTime;
	}
}