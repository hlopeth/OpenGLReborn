#pragma once
#include "EventHandlerBase.h"

template < class T, class EventT > class EventHandler : public EventHandlerBase
{
public:
	typedef void (T::* MemberHandler)(const EventT&);
	EventHandler(T* instance, MemberHandler handler) : _instance(instance), _handler(handler) {};
	void intCall(const Event& event) override
	{
		(_instance->*_handler)(static_cast<const EventT&>(event));
	}

private:
	T* _instance;
	MemberHandler _handler;
};