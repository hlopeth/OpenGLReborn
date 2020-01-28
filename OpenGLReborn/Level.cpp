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

	UI::VerticalLayout* layout = new UI::VerticalLayout();
	layout->setSize(vec2(500, 1.0));
	layout->useNormalizedCoords.w = true;
	layout->spacing = 10;

	UI::UIRect* rect1 = new UI::UIRect();
	rect1->setPosition(vec2(0.1, 0));
	rect1->useNormalizedCoords.x = true;
	rect1->setSize(vec2(0.8, 100));
	rect1->useNormalizedCoords.z = true;
	rect1->color = glm::vec4(1.0, 0.0, 0.0, 1.0);

	UI::UIRect* rect2 = new UI::UIRect();
	rect2->setPosition(vec2(0.1, 0));
	rect2->useNormalizedCoords.x = true;
	rect2->setSize(vec2(0.8, 100));
	rect2->useNormalizedCoords.z = true;
	rect2->color = glm::vec4(0.0, 1.0, 0.0, 1.0);

	UI::Button* btn = new UI::Button();
	btn->setPosition(vec2(0.1, 0));
	btn->useNormalizedCoords.x = true;
	btn->setSize(vec2(0.8, 100));
	btn->useNormalizedCoords.z = true;
	layout->addChild(rect1);
	layout->addChild(rect2);
	layout->addChild(btn);

	Canvas& c = uiRoot.getCanvas();
	c.addChild(layout);
	c.align(Rect(0, 0, WindowManager().windowWidth, WindowManager().windowHeight));


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
	{
		auto re = (ResizeEvent&)event;
		uiRoot.getCanvas().align(Rect(0, 0, re.width, re.height));
		break;
	}
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