#pragma once
#include "Renderer.h"

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
	Renderer& getRenderer();
private:
	static Renderer* renderer;
};