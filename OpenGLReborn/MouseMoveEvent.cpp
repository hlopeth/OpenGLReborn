#include "MouseMoveEvent.h"

MouseMoveEvent::MouseMoveEvent(float _xPosition, float _yPosition, float _xOffset, float _yOffset):
	Event(MOUSE_MOVE_EVENT),
	xPosition(_xPosition),
	yPosition(_yPosition),
	xOffset(_xOffset),
	yOffset(_yOffset)
{}
