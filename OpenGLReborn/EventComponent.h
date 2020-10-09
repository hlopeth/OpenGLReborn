#pragma once
#include <map>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "EventHandler.h"

using std::map;
using std::type_index;

class EventComponent
{
public:
	virtual void call(const Event& event);
	template < class T, class EventT > void setEventHandler(T* obj, void (T::* handler)(const EventT&))
	{
		handlers[type_index(typeid(EventT))] = new EventHandler<T, EventT>(obj, handler);
	}
private:
	map<type_index, EventHandlerBase*> handlers;
};