#include "StereoRenderer.h"
#include "MeshPrimitives.h"

const float eyeDist = 0.1; 
const float convergenceDist = 50;

StereoRenderer::StereoRenderer(GLFWwindow& _window):
	window(_window),
	leftEyeRenderTarget(WindowManager::windowWidth, WindowManager::windowHeight),
	rightEyeRenderTarget(WindowManager::windowWidth, WindowManager::windowHeight),
	screenRect(make_shared<Mesh>(RenderingPrimitives::Plane()), make_shared<FullscreenTextureMaterial>())
{
	viewportWidth = WindowManager::windowWidth;
	viewportHeight = WindowManager::windowHeight;
	setEventHandler<StereoRenderer, ResizeEvent>(this, &StereoRenderer::resize);
	glViewport(0, 0, viewportWidth, viewportHeight);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	screenMaterial = make_shared<FullscreenTextureMaterial>(
		FullscreenTextureMaterial(
			leftEyeRenderTarget.getTexture(),
			rightEyeRenderTarget.getTexture()
		)
		);
	screenRect.setMaterial(screenMaterial);
}

StereoRenderer::~StereoRenderer()
{
}

void StereoRenderer::draw(Level& level)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	const Camera& lvlCamera = level.getCamera();

	float aspect = ((float)viewportWidth) / viewportHeight;
	float tfov2 = tan(lvlCamera.fov);
	float top = lvlCamera.Near() * tfov2;
	float dist = eyeDist / 2.0f;
	float a = aspect * tfov2 * convergenceDist;
	float b = a - dist;
	float c = a + dist;
	float s = lvlCamera.Near() / convergenceDist;

	mat4 leftEyeProj = glm::frustum(-b * s, c * s, -top, top, lvlCamera.Near(), lvlCamera.Far());
	mat4 rightEyeProj = glm::frustum(-c * s, b * s, -top, top, lvlCamera.Near(), lvlCamera.Far());

	Camera leftEyeCamera = Camera(
		lvlCamera.pos - lvlCamera.Right() * eyeDist, 
		lvlCamera.front, 
		lvlCamera.up, 
		leftEyeProj
	);
	Camera rightEyeCamera = Camera(
		lvlCamera.pos + lvlCamera.Right() * eyeDist,
		lvlCamera.front, 
		lvlCamera.up, 
		rightEyeProj
	);

	drawLeftEye(level, leftEyeCamera);
	drawRightEye(level, rightEyeCamera);

	screenMaterial->textureLeft = leftEyeRenderTarget.getTexture();
	screenMaterial->textureRight = rightEyeRenderTarget.getTexture();
	RenderData renderData(leftEyeCamera, level.getScene().getPointLights(), level.getScene().getDirectinalLight());
	screenRect.draw(renderData);

	glfwSwapBuffers(&window);
}

void StereoRenderer::drawLeftEye(const Level& level, const Camera& leftEyeCamera)
{
	glBindFramebuffer(GL_FRAMEBUFFER, leftEyeRenderTarget.getFbo());
	drawCommon(level, leftEyeCamera);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void StereoRenderer::drawRightEye(const Level& level, const Camera& rightEyeCamera)
{
	glBindFramebuffer(GL_FRAMEBUFFER, rightEyeRenderTarget.getFbo());
	drawCommon(level, rightEyeCamera);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void StereoRenderer::drawCommon(const Level& level, const Camera& camera)
{
	glViewport(0, 0, viewportWidth, viewportHeight);
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	const Scene& scene = level.getScene();
	auto gameObjects = scene.getGameObjects();
	RenderData renderData(camera, scene.getPointLights(), scene.getDirectinalLight());


	glStencilMask(0x00);

	for (auto gameObject : gameObjects)
	{
		gameObject->draw(renderData);
	}

	if (scene.getSkyBox() != nullptr)
	{
		scene.getSkyBox()->draw(renderData);
	}
	level.getUIRoot().draw(renderData);
}

void StereoRenderer::resize(const ResizeEvent& event)
{
	viewportWidth = event.width;
	viewportHeight = event.height;
	leftEyeRenderTarget.allocate(viewportWidth, viewportHeight);
	rightEyeRenderTarget.allocate(viewportWidth, viewportHeight);
}
