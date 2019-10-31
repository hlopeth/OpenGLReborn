#pragma once
#include "Event.h"

class ResizeEvent : public Event
{
public:
	ResizeEvent(int _width, int _height) : 
		Event(EventType::RESIZE_EVENT),
		width(_width), 
		height(_height) {};
	int width;
	int height;
};