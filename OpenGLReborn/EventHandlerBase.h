#pragma once
#include "Event.h"

class EventHandlerBase
{
public:
	virtual ~EventHandlerBase();
	void invoke(const Event& event);
	void call(const Event& event);
private:
	virtual void intCall(const Event& event) = 0;
};
