#pragma once
#include "GameObject.h"
#include "Canvas.h"

using UI::Canvas;

class UIRoot : public GameObject
{
public:
	UIRoot();
	void draw(Camera& camera) override;
	Canvas& getCanvas();
	void setCanvas(Canvas canvas);
	void setRenderArea(float x, float y, float width, float height);
	Rect getRenderArea();
private:
	Canvas canvas;
	Rect renderArea;
};
