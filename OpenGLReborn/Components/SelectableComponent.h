#pragma once
#include "EventComponent.h"
#include "Event/SelectEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseMoveEvent.h"
#include "Event/MouseClickEvent.h"
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