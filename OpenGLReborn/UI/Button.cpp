#include "Button.h"
#include "Event/ExitEvent.h"
#include "Managers/LevelManager.h"
#include "UIRect.h"

UI::Button::Button() : UIWiget()
{
}

int UI::Button::getMaxChildren()
{
	return 1;
}

void UI::Button::draw() const
{
	drawChildren();
}