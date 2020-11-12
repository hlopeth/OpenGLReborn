#include "SelectableComponent.h"
#include <GLFW\glfw3.h>
#include "LevelManager.h"
#include <glm/vec3.hpp>

SelectableComponent::SelectableComponent(GameObject* _holder)
{
	holder = _holder;
	selected = false;
	rotateObj = false;
	holder->setEventHandler<SelectableComponent, SelectEvent>(this, &SelectableComponent::onSelectEvent);
}

SelectableComponent::~SelectableComponent()
{
	holder->removeEventHandler<SelectEvent>();
	holder->removeEventHandler<KeyEvent>();
	holder->removeEventHandler<MouseMoveEvent>();
	holder->removeEventHandler<MouseRightClickEvent>();
}

void SelectableComponent::onKeyEvent(const KeyEvent& event)
{
	if (event.action == GLFW_PRESS && event.key == GLFW_KEY_R)
	{
		selected = false;
		onDeselectRegister = true;
		LEVEL.getCamera().free();
	}
}

void SelectableComponent::onMouseClickEvent(const MouseRightClickEvent& event)
{
	rotateObj = event.pressed;
}

void SelectableComponent::onMouseMoveEvent(const MouseMoveEvent& event)
{
	if (!rotateObj)
		return;

	auto camera = LEVEL.getCamera();
	vec3 rotation = holder->getRotation();
	rotation.x += glm::radians(-event.yOffset);
	rotation.y += glm::radians(event.xOffset);
	holder->setRotation(rotation);
}

void SelectableComponent::onSelectEvent(const SelectEvent& event)
{
	selected = true;
	onSelectRegister = true;
	LEVEL.getCamera().lock();
}

void SelectableComponent::registerEvents()
{
	if (onSelectRegister)
	{
		holder->setEventHandler<SelectableComponent, KeyEvent>(this, &SelectableComponent::onKeyEvent);
		holder->setEventHandler<SelectableComponent, MouseMoveEvent>(this, &SelectableComponent::onMouseMoveEvent);
		holder->setEventHandler<SelectableComponent, MouseRightClickEvent>(this, &SelectableComponent::onMouseClickEvent);
		holder->removeEventHandler<SelectEvent>();
		onSelectRegister = false;
	}
	if (onDeselectRegister)
	{
		holder->removeEventHandler<KeyEvent>();
		holder->removeEventHandler<MouseMoveEvent>();
		holder->removeEventHandler<MouseRightClickEvent>();
		holder->setEventHandler<SelectableComponent, SelectEvent>(this, &SelectableComponent::onSelectEvent);
		onDeselectRegister = false;
	}
}
