#pragma once

enum EventType
{
	RESIZE_EVENT,
	MOUSE_MOVE_EVENT,

};

class Event 
{
public:
	EventType getType();
	Event(EventType _type);
private:
	EventType type;
};
