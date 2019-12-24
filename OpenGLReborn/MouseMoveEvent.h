#pragma once
#include "Event.h"

class MouseMoveEvent: public Event
{
public:
	MouseMoveEvent(float _xPosition, float _yPosition, float _xOffset = 0, float _yOffset = 0);
	int xPosition;
	int yPosition;
	int xOffset;
	int yOffset;
};