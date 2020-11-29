#include "UIEvent.h"

UIEvent::UIEvent(EventType _eventType, float _xPosition, float _yPosition): 
	Event(_eventType), 
	x(_xPosition), 
	y(_yPosition)
{
}
