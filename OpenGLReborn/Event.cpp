#include "Event.h"

EventType Event::getType()
{
	return type;
}

Event::Event(EventType _type)
{
	type = _type;
}

Event::~Event()
{
}
