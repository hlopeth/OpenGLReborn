#include "Level.h"
#include "MouseMoveEvent.h"
#include "ResizeEvent.h"
#include "ExitEvent.h"
#include "Triangle.h"
#include "Nanosuit.h"
#include "UIRect.h"
#include "Button.h"
#include "VerticalLayout.h"
#include "UIRoot.h"

Level::Level():
	camera(vec3(0.0), vec3(0.0), vec3(0.0))
{
	Triangle* triangle = new Triangle();

	Canvas& c = uiRoot.getCanvas();
	WindowManager wm = WindowManager();
	UI::VerticalLayout* layout = new UI::VerticalLayout();
	layout->setSize(vec2(500, wm.windowHeight));
	layout->spacing = 10;
	c.addChild(layout);

	UI::UIRect* rect1 = new UI::UIRect();
	rect1->setSize(vec2(layout->transform.width, 100));
	rect1->color = glm::vec4(1.0, 0.0, 0.0, 1.0);
	layout->addChild(rect1);

	UI::UIRect* rect2 = new UI::UIRect();
	rect2->setSize(vec2(layout->transform.width, 100));
	rect2->color = glm::vec4(0.0, 1.0, 0.0, 1.0);
	layout->addChild(rect2);

	UI::Button* btn = new UI::Button();
	btn->setSize(vec2(layout->transform.width, 100));
	layout->addChild(btn);

	auto background = new UI::UIRect();
	background->setSize(btn->getSize());
	btn->addChild(background);

	scene.addGameObject(triangle);

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

UIRoot& Level::getUIRoot()
{
	return uiRoot;
}

void Level::call(Event& event)
{
	switch (event.getType())
	{
	case RESIZE_EVENT:
	case MOUSE_MOVE_EVENT: 
	case MOUSE_CLICK_LEFT:
	case MOUSE_CLICK_RIGHT:
		uiRoot.getCanvas().call((UIEvent&)event);
		camera.call(event);
		break;
	case EXIT_EVENT:
		glfwSetWindowShouldClose(&WINDOW, GLFW_TRUE);
	default:
		break;
	}
}