#pragma once

class Rect
{
public:
	Rect();
	Rect(float _x, float _y, float _width, float _height);		
	bool containPoint(float px, float py);
	float x;
	float y;
	float width;
	float height;
};