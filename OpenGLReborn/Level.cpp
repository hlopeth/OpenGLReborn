#include "Level.h"
#include "Triangle.h"
#include "Nanosuit.h"

Level::Level():
	camera(vec3(0.0), vec3(0.0), vec3(0.0))
{
	Triangle* triangle = new Triangle();
	Nanosuit* nanosuit = new Nanosuit();
	scene.addGameObject(triangle);
	scene.addGameObject(nanosuit);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = Camera(cameraPos, cameraFront, cameraUp);
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

void Level::call(Event& event)
{
}
