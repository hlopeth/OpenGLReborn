#pragma once

#include <openvr/openvr.h>
#include "Scene.h"

using namespace vr;

class VrRenderer
{
public:
	VrRenderer(GLuint scr_width, GLuint scr_height);
	void Init();
	void Render(Scene scene);
	void Destroy();
protected:
	bool initTextures();
	vec3 getHeadPosition();
	mat4 getViewPosition(Hmd_Eye nEye);

	IVRSystem* vrSystem;
	bool initialized;
	GLuint leftEyeTexture;
	GLuint rightEyeTexture;
	GLuint leftEyeRbo;
	GLuint rightEyeRbo;
	GLuint leftEyeFBO;
	GLuint rightEyeFBO;
	GLuint scr_width, scr_height;
};