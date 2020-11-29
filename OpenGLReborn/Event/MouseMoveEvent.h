#pragma once
#include "UIEvent.h"

class MouseMoveEvent: public UIEvent
{
public:
	MouseMoveEvent(double _xPosition, double _yPosition, double _xOffset, double _yOffset);
	double xOffset;
	double yOffset;
};