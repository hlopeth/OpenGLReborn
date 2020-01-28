#include "KeyEvent.h"

KeyEvent::KeyEvent(int _key, int _action): key(_key), action(_action), Event(KEY_EVENT)
{
}
