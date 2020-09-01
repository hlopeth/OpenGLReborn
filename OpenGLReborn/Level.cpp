#include "Level.h"
#include "MouseClickEvent.h"
#include "ResizeEvent.h"
#include "ExitEvent.h"
#include "Triangle.h"
#include "Nanosuit.h"
#include "UIRect.h"
#include "Button.h"
#include "Box.h"
#include "VerticalLayout.h"
#include "UIRoot.h"
#include "Lamp.h"
#include "MainMenu.h"
#include "Trace.h"
#include "Event.h"
#include "Plane.h"
#include "BoxPhysicsShape.h"

void setupUI(UIRoot& uiRoot)
{
	Canvas& c = uiRoot.getCanvas();
	UI::MainMenu* mainMenu = new UI::MainMenu();
	mainMenu->visible = false;
	c.addChild(mainMenu);
}

Level::Level():
	camera(vec3(0.0), vec3(0.0), vec3(0.0))
{
	setupUI(uiRoot);

	//уровень пока строится прямо в конструкторе
	Nanosuit* nanosuit = new Nanosuit();
	nanosuit->physicsBody = new BoxPhysicsShape(*nanosuit, 1.f);
	Lamp* lampWhite = new Lamp();
	lampWhite->pointLight.diffuse = vec3(0.8);
	Lamp* lampRed = new Lamp();
	lampRed->setPosition(vec3(0.0, 15.0, -5.0));
	lampRed->pointLight.diffuse = vec3(0.8, 0.1, 0.1);
	Lamp* lampBlue = new Lamp();		
	lampBlue->setPosition(vec3(0.0, 15.0, 5.0));
	lampBlue->pointLight.diffuse = vec3(0.1, 0.1, 0.8);
	Plane* plane = new Plane();
	plane->setPosition(vec3(0.0, -5.0, 0.0));
	plane->setScale(vec3(50.f, 1.0f, 50.f));
	plane->physicsBody = new BoxPhysicsShape(*plane, 0.f);
	
	scene.addGameObject(nanosuit);
	scene.addGameObject(lampWhite);
	scene.addGameObject(lampRed);
	scene.addGameObject(lampBlue);
	scene.addGameObject(plane);
	scene.addPointLight(&(lampWhite->pointLight));
	scene.addPointLight(&(lampRed->pointLight));
	scene.addPointLight(&(lampBlue->pointLight));

	camera.pos = glm::vec3(0.0f, 0.0f, 10.0f);
	camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->setEventHandler<Level, KeyEvent>(this, &Level::onKey);
	this->setEventHandler<Level, ExitEvent>(this, &Level::onExit);
}

void Level::update(double gameTime, double deltaTime)
{
	camera.update(gameTime, deltaTime);
}

Camera& Level::getCamera()
{
	return camera;
}

Scene& Level::getScene()
{
	return scene;
}

UIRoot& Level::getUIRoot()
{
	return uiRoot;
}

void Level::afterPhysicsUpdate()
{
	auto gameObjects = scene.getGameObjects();
	for (auto gameObject : gameObjects) {
		gameObject->afterPhysicsUpdate();
	}
}

void Level::onKey(const KeyEvent& event)
{
	if (event.key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(&WINDOW, true);
	}
}

void Level::onExit(const ExitEvent& event)
{
	glfwSetWindowShouldClose(&WINDOW, true);
}

void Level::call(const Event& event)
{
	EventComponent::call(event);
	camera.call(event);
	uiRoot.call(event);
}
