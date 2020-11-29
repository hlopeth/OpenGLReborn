#pragma once
#include "EventHandlerBase.h"

template <class EventT > class EventHandler : public EventHandlerBase
{
public:
	typedef void (*Handler)(const EventT&);
	EventHandler(Handler handler) : _handler(handler) {};
	void intCall(const Event& event) override
	{
		(*_handler)(static_cast<const EventT&>(event));
	}

private:
	Handler _handler;
};

template < class T, class EventT > class MemberEventHandler : public EventHandlerBase
{
public:
	typedef void (T::* MemberHandler)(const EventT&);
	MemberEventHandler(T* instance, MemberHandler handler) : _instance(instance), _handler(handler) {};
	void intCall(const Event& event) override
	{
		(_instance->*_handler)(static_cast<const EventT&>(event));
	}

private:
	T* _instance;
	MemberHandler _handler;
};