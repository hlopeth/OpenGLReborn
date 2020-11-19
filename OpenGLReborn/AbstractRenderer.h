#pragma once
#include <GLFW/glfw3.h>
#include "Level.h"
#include "EventComponent.h"

class AbstractRenderer: public EventComponent
{
public:
	virtual void draw(Level& level) = 0;
};