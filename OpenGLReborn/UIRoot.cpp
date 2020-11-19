#include "UIRoot.h"
#include "WindowManager.h"

UIRoot::UIRoot()
{
	auto wm = WindowManager();
	renderArea = Rect(0, 0, wm.windowWidth, wm.windowHeight);
	canvas = Canvas();
	canvas.setPosition(vec2(0, 0));
	canvas.setSize(vec2(renderArea.width, renderArea.height));
}

void UIRoot::draw(RenderData& renderData) const
{
	canvas.draw();
}

Canvas& UIRoot::getCanvas()
{
	return canvas;
}

void UIRoot::setCanvas(Canvas canvas)
{
	this->canvas = canvas;
}

void UIRoot::setRenderArea(float x, float y, float width, float height)
{
	renderArea.x = x;
	renderArea.y = y;
	renderArea.width = width;
	renderArea.height = height;
}

Rect UIRoot::getRenderArea()
{
	return renderArea;
}

void UIRoot::call(const Event& event)
{
	EventComponent::call(event);
	canvas.call(event);
}
