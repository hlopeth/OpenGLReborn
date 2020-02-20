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

	Nanosuit* nanosuit = new Nanosuit();
	Lamp* lampWhite = new Lamp();
	lampWhite->pointLight.diffuse = vec3(0.8);
	Lamp* lampRed = new Lamp();
	lampRed->setPosition(vec3(0.0, 15.0, -5.0));
	lampRed->pointLight.diffuse = vec3(0.8, 0.1, 0.1);
	Lamp* lampBlue = new Lamp();
	lampBlue->setPosition(vec3(0.0, 15.0, 5.0));
	lampBlue->pointLight.diffuse = vec3(0.1, 0.1, 0.8);
	

	scene.addGameObject(nanosuit);
	scene.addGameObject(lampWhite);
	scene.addGameObject(lampRed);
	scene.addGameObject(lampBlue);
	scene.addPointLight(&(lampWhite->pointLight));
	scene.addPointLight(&(lampRed->pointLight));
	scene.addPointLight(&(lampBlue->pointLight));

	camera.pos = glm::vec3(0.0f, 0.0f, 10.0f);
	camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->setEventHandler<Level, KeyEvent>(this, &Level::onKey);
}

void Level::update()
{
	double prevTime = time;
	time = glfwGetTime();
	double deltaTime = time - prevTime;

	camera.update(time, deltaTime);
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

void Level::onKey(const KeyEvent& event)
{
	if (event.key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(&WINDOW, true);
	}
}

void Level::call(const Event& event)
{
	EventComponent::call(event);
	camera.call(event);
	uiRoot.call(event);
}
