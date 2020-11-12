#pragma once
#include "EventComponent.h"
#include "SelectEvent.h"
#include "KeyEvent.h"
#include "MouseMoveEvent.h"
#include "MouseClickEvent.h"
#include "GameObject.h"

class SelectableComponent
{
public:
	SelectableComponent(GameObject *holder);
	~SelectableComponent();
	void registerEvents();
private:
	void onKeyEvent(const KeyEvent& event);
	void onMouseClickEvent(const MouseRightClickEvent& event);
	void onMouseMoveEvent(const MouseMoveEvent& event);
	void onSelectEvent(const SelectEvent& event);
	bool selected;
	GameObject* holder;
	bool rotateObj;
	bool onSelectRegister = false;
	bool onDeselectRegister = false;
};