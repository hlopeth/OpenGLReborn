#include "UIWiget.h"
#include "Trace.h"

using namespace UI;

UIWiget::UIWiget()
{
}

UIWiget::UIWiget(float x, float y, float width, float height) : UIWiget()
{
	transform = Rect(x, y, width, height);
}

UIWiget::UIWiget(Rect transform): UIWiget()
{
	this->transform = transform;
}

vec2 UIWiget::getPosition()
{
	return vec2(transform.x, transform.y);
}

vec2 UIWiget::getSize()
{
	return vec2(transform.width, transform.height);
}

void UIWiget::setPosition(const vec2 position)
{
	transform.x = position.x;
	transform.y = position.y;
}

void UIWiget::setSize(const vec2 size)
{
	transform.width = size.x;
	transform.height = size.y;
}

void UI::UIWiget::setSize(float width, float height)
{
	setSize(vec2(width, height));
}

std::vector<const UIWiget*> UIWiget::getChildren()
{
	std::vector<const UIWiget*> childrenCopy;
	for (auto i = children.begin(); i != children.end(); i++)
	{
		childrenCopy.push_back(*i);
	}
	return childrenCopy;
}

void UI::UIWiget::call(const Event& event)
{
	EventComponent::call(event);
	for (auto child : children)
	{
		child->call(event);
	}
}

bool UI::UIWiget::addChild(UIWiget* wiget)
{
	if (children.size() >= getMaxChildren())
	{
		return false;
	}

	children.push_back(wiget);
	wiget->parent = this;
	wiget->transform.x += transform.x;
	wiget->transform.y += transform.y;
	return true;
}

void UI::UIWiget::drawChildren()
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		if ((*i)->visible) 
		{
			(*i)->draw();
		}
	}
}

bool UI::UIWiget::pointInShape(float _x, float _y)
{
	return _x >= transform.x && 
		_y >= transform.y && 
		_x <= transform.x + transform.width &&
		_y <= transform.y + transform.height;
}
