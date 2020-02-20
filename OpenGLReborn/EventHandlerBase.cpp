#include "EventHandlerBase.h"

EventHandlerBase::~EventHandlerBase()
{
}

void EventHandlerBase::invoke(const Event& event)
{
	call(event);
}

void EventHandlerBase::call(const Event& event)
{
	intCall(event);
}
