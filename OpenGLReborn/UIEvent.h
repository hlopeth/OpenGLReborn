#pragma once
#include "Event.h"

class UIEvent : public Event
{
public:
	UIEvent(EventType _eventType, float _x, float _y);
	float x;
	float y;
};
