#include "Button.h"
#include "ExitEvent.h"
#include "LevelManager.h"
#include "UIRect.h"

UI::Button::Button() : UIWiget()
{
	auto background = new UIRect(vec4(0,0,0,1));
	
	addChild(background);
}

void UI::Button::call(UIEvent& event)
{
	UIWiget::call(event);

	if (globalTransform.hasPoint(event.x, event.y))
	{
		switch (event.getType())
		{
		case MOUSE_CLICK_LEFT:
		{
			ExitEvent ev = ExitEvent();
			LEVEL.call(ev);
			break;
		}
		default:
			break;
		}
	}

}

int UI::Button::getMaxChildren()
{
	return 1;
}

void UI::Button::draw(const Rect& renderArea)
{
	drawChildren(globalTransform);
}