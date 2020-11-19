#pragma once
#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include "AbstractRenderer.h"
#include "ResizeEvent.h"
#include "Camera.h"

class StereoRenderer : public AbstractRenderer
{
public:
	StereoRenderer(GLFWwindow& window);
	~StereoRenderer();
	void draw(Level& level) override;
	static const int glMajorVersion = 4;
	static const int glMinorVersion = 4;
private:
	void drawLeftEye(const Level& level, const Camera& leftEyeCamera);
	void drawRightEye(const Level& level, const Camera& leftEyeCamera);
	void drawCommon(const Level& level, const Camera& camera);
	void resize(const ResizeEvent& event);

	GLFWwindow& window;
	int viewportWidth = 0;
	int viewportHeight = 0;
};