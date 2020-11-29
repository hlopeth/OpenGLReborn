#include "EventComponent.h"

void EventComponent::call(const Event& event)
{	
	auto foundHandlers = handlers.find(typeid(event));
	if (foundHandlers != handlers.end())
	{
		(*foundHandlers).second->invoke(event);		
	}
}
