#include "VerticalLayout.h"
#include "Trace.h"

bool UI::VerticalLayout::addChild(UIWiget* wiget)
{
	bool result = UIWiget::addChild(wiget);
	return result;
}

int UI::VerticalLayout::getMaxChildren()
{
	return maxChildren;
}

void UI::VerticalLayout::call(UIEvent& event)
{
	UIWiget::call(event);
}

void UI::VerticalLayout::draw(const Rect& renderArea)
{
	Rect childRenderArea = Rect(renderArea);
	for (auto pChild = children.begin(); pChild != children.end(); pChild++)
	{
		auto child = (*pChild);
		childRenderArea.height = child->getSize().y;
		child->draw(childRenderArea);
		childRenderArea.y += child->getSize().y + spacing;
	}
}

void UI::VerticalLayout::align(Rect parentTransform)
{
	globalTransform.x = transform.x + parentTransform.x;
	globalTransform.y = transform.y + parentTransform.y;
	globalTransform.width = useNormalizedCoords.x ? transform.width * parentTransform.width : transform.width;
	globalTransform.height = useNormalizedCoords.y ? transform.height * parentTransform.height : transform.height;

	if (alignChildren)
	{
		Rect childTransform = Rect(globalTransform.x, globalTransform.y, globalTransform.width, 0);
		for (auto child : children)
		{
			childTransform.height = child->getSize().y;
			child->align(childTransform);
			childTransform.y += child->getSize().y + spacing;
		}
	}
}