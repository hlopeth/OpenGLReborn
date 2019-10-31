#include "InputManager.h"
#include "WindowManager.h"

Input* InpuManager::input = nullptr;

void InpuManager::initialise()
{
	input = new Input(WindowManager().getWindow());
}

void InpuManager::destroy()
{
	input = nullptr;
}

Input& InpuManager::getInput()
{
	return *input;
}
