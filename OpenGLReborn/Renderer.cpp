#include "Renderer.h"
#include "InitialisationExeption.h"
#include "ResizeEvent.h"
#include "WindowManager.h"
#include "Trace.h"

Renderer::Renderer( GLFWwindow &window) : window(window)
{
	viewportWidth = WindowManager::windowWidth;
	viewportHeight = WindowManager::windowHeight;
}

Renderer::~Renderer()
{

}

void checkGLErrors()
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

void Renderer::draw(Level& level)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glViewport(0, 0, viewportWidth, viewportHeight);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<GameObject*> gameObjects = level.getScene().getGameObjects();
	Camera& camera = level.getCamera();

	for (auto gameObject : gameObjects)
	{
		gameObject->draw(camera);
	}

	checkGLErrors();
	glfwSwapBuffers(&window);
}

void Renderer::call(Event& event)
{
	switch (event.getType())
	{
	case EventType::RESIZE_EVENT:
		auto re = (ResizeEvent&)(event);
		viewportWidth = re.width;
		viewportHeight = re.height;
		break;
	}
}
