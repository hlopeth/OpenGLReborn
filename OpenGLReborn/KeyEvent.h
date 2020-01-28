#pragma once
#include "Event.h"

class KeyEvent : public Event
{
public:
	KeyEvent(int key, int action);
	const int key;
	const int action;
};
