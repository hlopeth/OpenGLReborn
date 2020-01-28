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

bool UI::UIWiget::inShape(UIEvent& event)
{
	vec2 pos = getPosition();
	vec2 size = getSize();
	return  event.x >= pos.x && event.x <= pos.x + size.x && event.y >= pos.y && event.y <= pos.y + size.y;
}

//событие в экранных координатах(если он есть) 
void UI::UIWiget::call(UIEvent& event)
{
	//проверка попадания события
	if (globalTransform.hasPoint(event.x, event.y))
	{
		for (auto child : children)
		{
			child->call(event);
		}
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
	return true;
}

void UI::UIWiget::align(Rect parentTransform)
{
	globalTransform.x = parentTransform.x + useNormalizedCoords.x ? transform.x * parentTransform.width : transform.x;
	globalTransform.y = parentTransform.y + useNormalizedCoords.y ? transform.y * parentTransform.height: transform.y;
	globalTransform.width = useNormalizedCoords.z ? transform.width * parentTransform.width : transform.width;
	globalTransform.height = useNormalizedCoords.w ? transform.height * parentTransform.height : transform.height;

	if (alignChildren)
	{
		for (auto child : children)
		{
			child->align(globalTransform);
		}
	}
}

void UI::UIWiget::drawChildren(const Rect& renderArea)
{
	for (auto i = children.begin(); i != children.end(); i++)
	{
		(*i)->draw(renderArea);
	}
}
