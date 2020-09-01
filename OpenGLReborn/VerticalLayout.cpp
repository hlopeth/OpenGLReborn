#include "VerticalLayout.h"
#include "Trace.h"

bool UI::VerticalLayout::addChild(UIWiget* wiget)
{
	bool isAdded = UIWiget::addChild(wiget);
	if (isAdded)
	{
		wiget->transform.y += nextChildrenY;
		nextChildrenY += wiget->getSize().y + spacing;
	}
	return isAdded;
}

int UI::VerticalLayout::getMaxChildren()
{
	return maxChildren;
}

void UI::VerticalLayout::draw()
{
	drawChildren();
}
