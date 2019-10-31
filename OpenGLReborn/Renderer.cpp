#include "Renderer.h"
#include "InitialisationExeption.h"
#include "ResizeEvent.h"

Renderer::Renderer( GLFWwindow &window) : window(window)
{
	glfwMakeContextCurrent(&window);

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

Renderer::~Renderer()
{

}

void Renderer::draw(Scene& scene)
{
	throw "TODO";
}

void Renderer::call(Event& event)
{
	switch (event.getType())
	{
	case EventType::RESIZE_EVENT:
		auto re = (ResizeEvent&)(event);
		glViewport(0, 0, re.width, re.height);
		break;
	}
}
