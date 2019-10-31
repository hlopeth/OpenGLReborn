#pragma once
#include "Renderer.h"

/*
	require WindowManager
*/
class RendererManager
{
public:
	void initialise();
	void destroy();
	Renderer& getRenderer();
private:
	static Renderer* renderer;
};