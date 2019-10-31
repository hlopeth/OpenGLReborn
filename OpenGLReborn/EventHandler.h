#pragma once
#include "Event.h"

class EventHandler
{
public:
	virtual void call(Event& event) = 0;
};