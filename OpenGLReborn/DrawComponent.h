#pragma once
#include "Camera.h"

class DrawComponent
{
public:
	virtual void draw(Camera& camera) = 0;
};

