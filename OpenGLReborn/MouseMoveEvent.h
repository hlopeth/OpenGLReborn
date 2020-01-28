#pragma once
#include "UIEvent.h"

class MouseMoveEvent: public UIEvent
{
public:
	MouseMoveEvent(float _xPosition, float _yPosition, float _xOffset = 0, float _yOffset = 0);
	int xOffset;
	int yOffset;
};