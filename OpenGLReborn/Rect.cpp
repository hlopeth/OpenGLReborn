#include "Rect.h"

Rect::Rect()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rect::Rect(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height)
{
}

bool Rect::containPoint(float px, float py)
{
	return px >= x && px <= (x + width) && py >= y && py <= (y + height);
}
