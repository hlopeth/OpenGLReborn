#include "Button.h"
#include "ExitEvent.h"
#include "LevelManager.h"
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