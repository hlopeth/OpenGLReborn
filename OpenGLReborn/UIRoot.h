#pragma once
#include "GameObject.h"
#include "Canvas.h"

using UI::Canvas;

class UIRoot : public GameObject
{
public:
	UIRoot();
	void draw(RenderData& renderData) const override;
	Canvas& getCanvas();
	void setCanvas(Canvas canvas);
	void setRenderArea(float x, float y, float width, float height);
	Rect getRenderArea();
	void call(const Event& event) override;
private:
	Canvas canvas;
	Rect renderArea;
};
