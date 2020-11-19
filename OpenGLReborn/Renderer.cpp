#include "Renderer.h"
#include "InitialisationExeption.h"
#include "ResizeEvent.h"
#include "WindowManager.h"
#include "Trace.h"

Renderer::Renderer( GLFWwindow &window) : window(window)
{
	viewportWidth = WindowManager::windowWidth;
	viewportHeight = WindowManager::windowHeight;
	glViewport(0, 0, viewportWidth, viewportHeight);
	glDepthFunc(GL_LEQUAL); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setEventHandler<Renderer, ResizeEvent>(this, &Renderer::resize);

	outlineShader = ShaderProgram("DefaultVertex.glsl", "DefaultFragment.glsl");
}

Renderer::~Renderer()
{

}


void Renderer::draw(Level& level)
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_MULTISAMPLE);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Scene& scene = level.getScene();
	vector<GameObject*> gameObjects = scene.getGameObjects();
	RenderData renderData(level.getCamera(), scene.getPointLights(), scene.getDirectinalLight());

	
	glStencilMask(0x00);

	for (auto gameObject : gameObjects)
	{
		if (gameObject != level.selectedModel) {
			gameObject->draw(renderData);
		}
	}

	if (scene.getSkyBox() != nullptr) 
	{
		scene.getSkyBox()->draw(renderData);
	}

	if (level.selectedModel != nullptr)
	{
		Model& selectedModel = *level.selectedModel;
		auto originalScale = selectedModel.getScale();

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		selectedModel.draw(renderData);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		selectedModel.setScale(originalScale * vec3(1.1));

		outlineShader.use();
		auto modelMatrix = selectedModel.getModelMatrix();
		auto mvp = renderData.camera.getViewProjection() * modelMatrix;
		outlineShader.setUniform("mvp", mvp);
		outlineShader.setUniform("model", modelMatrix);
		outlineShader.setUniform("color", vec3(1.0));

		glBindVertexArray(selectedModel.getMesh()->getVAO());
		glDrawElements(GL_TRIANGLES, selectedModel.getMesh()->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		selectedModel.setScale(originalScale);
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
	}

	level.getUIRoot().draw(renderData);

	glfwSwapBuffers(&window);
	checkGLErrors();
}

void Renderer::resize(const ResizeEvent& event)
{
	viewportWidth = event.width;
	viewportHeight = event.height;
	glViewport(0, 0, viewportWidth, viewportHeight);
}
