#pragma once

enum EventType
{
	RESIZE_EVENT,
	KEY_EVENT,
	MOUSE_MOVE_EVENT,
	MOUSE_CLICK_RIGHT,
	MOUSE_CLICK_LEFT,
	EXIT_EVENT
};

class Event 
{
public:
	EventType getType();
	Event(EventType _type);
	virtual ~Event();
private:
	EventType type;
};
