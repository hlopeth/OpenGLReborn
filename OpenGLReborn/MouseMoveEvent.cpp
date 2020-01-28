#include "MouseMoveEvent.h"

MouseMoveEvent::MouseMoveEvent(float _xPosition, float _yPosition, float _xOffset, float _yOffset):
	UIEvent(MOUSE_MOVE_EVENT, _xPosition, _yPosition),
	xOffset(_xOffset),
	yOffset(_yOffset)
{}
