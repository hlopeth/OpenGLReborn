#pragma once
#include "AbstractRenderer.h"

#ifndef RENDERER
#define RENDERER RendererManager().getRenderer()
#endif // !RENDERER

/*
	require WindowManager
*/
class RendererManager
{
public:
	void initialise();
	void destroy();
	AbstractRenderer& getRenderer();
private:
	static AbstractRenderer* renderer;
};