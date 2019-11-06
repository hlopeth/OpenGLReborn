#include "Renderer.h"
#include "InitialisationExeption.h"
#include "ResizeEvent.h"
#include "WindowManager.h"
#include "Trace.h"

Renderer::Renderer( GLFWwindow &window) : window(window)
{
	glfwMakeContextCurrent(&window);

	viewportWidth = WindowManager::windowWidth;
	viewportHeight = WindowManager::windowHeight;
}

Renderer::~Renderer()
{

}

void Renderer::draw(Level& level)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glViewport(0, 0, viewportHeight, viewportHeight);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	auto gameObjects = level.getScene().getGameObjects();
	auto camera = level.getCamera();

	for (auto gameObject : gameObjects)
	{
		gameObject.draw(camera);
	}

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
