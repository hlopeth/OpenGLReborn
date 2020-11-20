#pragma once
#include "Event.h"

class SelectEvent: public Event
{
public:
	SelectEvent();
};

class UnselectEvent: public Event
{
public:
	UnselectEvent();
};