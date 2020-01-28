#include "Canvas.h"

int UI::Canvas::getMaxChildren()
{
	return maxChildren;
}

void UI::Canvas::draw()
{
	drawChildren();
}