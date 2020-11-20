#pragma once
#include <map>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "EventHandlers.h"

using std::map;
using std::type_index;

class EventComponent
{
public:
	virtual void call(const Event& event);
	template < class T, class EventT > void setEventHandler(T* obj, void (T::* handler)(const EventT&))
	{
		handlers[type_index(typeid(EventT))] = new MemberEventHandler<T, EventT>(obj, handler);
	}
	template <class EventT > void setEventHandler(void (*handler)(const EventT&))
	{
		handlers[type_index(typeid(EventT))] = new EventHandler<EventT>(handler);
	}
	template <class EventT > void removeEventHandler()
	{
		auto handler = handlers.find(type_index(typeid(EventT)));
		if (handler != handlers.end())
		{
			handlers.erase(handler);
		}
	}
private:
	map<type_index, EventHandlerBase*> handlers;
};