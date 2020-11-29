#include "MouseMoveEvent.h"

MouseMoveEvent::MouseMoveEvent(double _xPosition, double _yPosition, double _xOffset, double _yOffset):
	UIEvent(MOUSE_MOVE_EVENT, _xPosition, _yPosition),
	xOffset(_xOffset),
	yOffset(_yOffset)
{}
