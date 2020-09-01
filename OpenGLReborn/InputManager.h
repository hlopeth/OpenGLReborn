#pragma once
#include "Input.h"

#ifndef INPUT
#define INPUT InputManager().getInput()
#endif // !INPUT


class InputManager
{
public:
	void initialise();
	void destroy();
	Input& getInput();
private:
	static Input* input;
};