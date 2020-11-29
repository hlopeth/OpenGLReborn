#include "MouseClickEvent.h"

MouseRightClickEvent::MouseRightClickEvent(float _x, float _y, bool _pressed) : UIEvent(MOUSE_CLICK_RIGHT, _x, _y), pressed(_pressed)
{
}

MouseLeftClickEvent::MouseLeftClickEvent(float _x, float _y, bool _pressed) : UIEvent(MOUSE_CLICK_LEFT, _x, _y), pressed(_pressed)
{
}
