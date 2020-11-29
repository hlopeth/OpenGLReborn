#include "InputManager.h"
#include "WindowManager.h"

Input* InputManager::input = nullptr;

void InputManager::initialise()
{
	input = new Input(WindowManager().getWindow());
}

void InputManager::destroy()
{
	delete(input);
	input = nullptr;
}

Input& InputManager::getInput()
{
	return *input;
}
