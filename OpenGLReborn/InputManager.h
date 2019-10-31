#pragma once
#include "Input.h"

class InpuManager
{
public:
	void initialise();
	void destroy();
	Input& getInput();
private:
	static Input* input;
};