#include "Level.h"
#include "Nanosuit.h"

Level::Level()
{
	Nanosuit nanosuit = Nanosuit();
	scene.addGameObject(nanosuit);
}

void Level::update()
{
}

Camera& Level::getCamera()
{
	return camera;
}

Scene& Level::getScene()
{
	return scene;
}
