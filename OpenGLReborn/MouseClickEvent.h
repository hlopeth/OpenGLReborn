#pragma once
#include "UIEvent.h"

class MouseRightClickEvent : public UIEvent
{
public:
	MouseRightClickEvent(float _x, float _y, bool _pressed);
	bool pressed;
};

class MouseLeftClickEvent : public UIEvent
{
public:
	MouseLeftClickEvent(float _x, float _y, bool _pressed);
	bool pressed;
};