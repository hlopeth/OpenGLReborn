#pragma once
#include <GLFW/glfw3.h>
#include "Level.h"
#include "EventComponent.h"
#include "Trace.h"

class AbstractRenderer: public EventComponent
{
public:
	virtual void draw(Level& level) = 0;
	static void checkGLErrors()
	{
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			switch (err)
			{
			case GL_INVALID_ENUM:
				trace("GL_INVALID_ENUM");
				break;
			case GL_INVALID_VALUE:
				trace("GL_INVALID_ENUM");
				break;
			case GL_INVALID_OPERATION:
				trace("GL_INVALID_OPERATION");
				break;
			case GL_STACK_OVERFLOW:
				trace("GL_STACK_OVERFLOW");
				break;
			case GL_STACK_UNDERFLOW:
				trace("GL_STACK_UNDERFLOW");
				break;
			case GL_OUT_OF_MEMORY:
				trace("GL_OUT_OF_MEMORY");
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				trace("GL_INVALID_FRAMEBUFFER_OPERATION");
				break;
			case GL_CONTEXT_LOST:
				trace("GL_CONTEXT_LOST");
				break;
			default:
				trace("GL_UNNOWN_ERROR");
				break;
			}
		}
	}
};