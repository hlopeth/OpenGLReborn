#pragma once
#include "RenderData.h"

class DrawComponent
{
public:
	virtual void draw(RenderData& renderData) const = 0;
};

