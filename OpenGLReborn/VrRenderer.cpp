//#include "VrRenderer.h"
//
//VrRenderer::VrRenderer(GLuint scr_width, GLuint scr_height)
//{
//	initialized = false;
//	vrSystem = nullptr;
//	leftEyeTexture = 0;
//	rightEyeTexture = 0;
//	leftEyeFBO = 0;
//	rightEyeFBO = 0;
//
//	this->scr_height = scr_height;
//	this->scr_width = scr_width;
//}
//
//void VrRenderer::Init()
//{
//	EVRInitError eError = VRInitError_None;
//	vrSystem = VR_Init(&eError, VRApplication_Scene);
//
//	if (eError != VRInitError_None)
//	{
//		initialized = false;
//		return;
//	}
//
//	eError = VRInitError_None;
//
//	if (!VRCompositor())
//	{
//		initialized = false;
//		return;
//	}
//
//	if (!initTextures())
//	{
//		initialized = false;
//		return;
//	}
//
//	initialized = true;
//}
//
//bool VrRenderer::initTextures()
//{
//	glGenFramebuffers(1, &leftEyeFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, leftEyeFBO);
//	glGenTextures(1, &leftEyeTexture);
//	glBindTexture(GL_TEXTURE_2D, leftEyeTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, scr_width, scr_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, leftEyeTexture, 0);
//
//	
//	glGenRenderbuffers(1, &leftEyeRbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, leftEyeRbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height); // use a single renderbuffer object for both a depth AND stencil buffer.
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, leftEyeRbo); // now actually attach it
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		return false;// cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
//
//
//	glGenFramebuffers(1, &rightEyeFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, rightEyeFBO);
//
//	glGenTextures(1, &rightEyeTexture);
//	glBindTexture(GL_TEXTURE_2D, rightEyeTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, scr_width, scr_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rightEyeTexture, 0);
//
//	glGenRenderbuffers(1, &rightEyeRbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rightEyeRbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height); // use a single renderbuffer object for both a depth AND stencil buffer.
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rightEyeRbo); // now actually attach it
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		return false; //cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	return true;
//}
//
//void VrRenderer::Destroy()
//{
//	glDeleteTextures(1, &leftEyeTexture);
//	glDeleteTextures(1, &rightEyeTexture);
//
//	glDeleteRenderbuffers(1, &leftEyeRbo);
//	glDeleteRenderbuffers(1, &rightEyeRbo);
//
//	glDeleteFramebuffers(1, &leftEyeFBO);
//	glDeleteFramebuffers(1, &rightEyeFBO);
//
//	VR_Shutdown();
//	initialized = false;
//}
//
//void VrRenderer::Render(Scene scene)
//{
//	if (!initialized)
//		return;
//
//	TrackedDevicePose_t trackedDevicePose_t[k_unMaxTrackedDeviceCount];
//	VRCompositor()->WaitGetPoses(trackedDevicePose_t, k_unMaxTrackedDeviceCount, nullptr, 0);
//	vec3 headPos = getHeadPosition();
//
//	//leftEye
//	glViewport(0, 0, scr_width, scr_height);
//	glBindFramebuffer(GL_FRAMEBUFFER, leftEyeFBO);
//	glEnable(GL_DEPTH_TEST);
//
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	mat4 viewProj = getViewPosition(Eye_Left);
//	scene.Draw(viewProj, headPos);
//
//	Texture_t leftEyeTexture_t = { (void*)(uintptr_t)leftEyeTexture,  TextureType_OpenGL, ColorSpace_Gamma };
//	VRCompositor()->Submit(Eye_Left, &leftEyeTexture_t);
//
//	//rightEye
//	glViewport(0, 0, scr_width, scr_height);
//	glBindFramebuffer(GL_FRAMEBUFFER, rightEyeFBO);
//	glEnable(GL_DEPTH_TEST);
//
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	viewProj = getViewPosition(Eye_Right);
//	scene.Draw(viewProj, headPos);
//
//	Texture_t rightEyeTexture_t = { (void*)(uintptr_t)rightEyeTexture, TextureType_OpenGL, ColorSpace_Gamma };
//	VRCompositor()->Submit(Eye_Right, &rightEyeTexture_t);
//}
//
//vec3 VrRenderer::getHeadPosition()
//{
//	TrackedDevicePose_t trackedDevicePose;
//	vrSystem->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, 0, &trackedDevicePose, 1);
//	HmdMatrix34_t mat34 = trackedDevicePose.mDeviceToAbsoluteTracking;
//	vec3 head_pos(mat34.m[0][3], mat34.m[1][3], mat34.m[2][3]);
//
//	return head_pos;
//}
//
//mat4 VrRenderer::getViewPosition(Hmd_Eye nEye)
//{
//	//proj
//	HmdMatrix44_t mat = vrSystem->GetProjectionMatrix(nEye, 0.1f, 100.0f);
//	mat4 proj(
//		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
//		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
//		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
//		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
//	);
//
//	//eye to head transform
//	HmdMatrix34_t mat34 = vrSystem->GetEyeToHeadTransform(nEye);
//	mat4 matrix_eyeToHead(
//		mat34.m[0][0], mat34.m[1][0], mat34.m[2][0], 0.0,
//		mat34.m[0][1], mat34.m[1][1], mat34.m[2][1], 0.0,
//		mat34.m[0][2], mat34.m[1][2], mat34.m[2][2], 0.0,
//		mat34.m[0][3], mat34.m[1][3], mat34.m[2][3], 1.0f
//	);
//	mat4 eyeToHeadTransform = inverse(matrix_eyeToHead);
//
//	//head
//	TrackedDevicePose_t trackedDevicePose;
//	vrSystem->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, 0, &trackedDevicePose, 1);
//	mat34 = trackedDevicePose.mDeviceToAbsoluteTracking;
//	mat4 matrix_head(
//		mat34.m[0][0], mat34.m[1][0], mat34.m[2][0], 0.0,
//		mat34.m[0][1], mat34.m[1][1], mat34.m[2][1], 0.0,
//		mat34.m[0][2], mat34.m[1][2], mat34.m[2][2], 0.0,
//		mat34.m[0][3], mat34.m[1][3], mat34.m[2][3], 1.0f
//	);
//	mat4 headMat = inverse(matrix_head);
//
//	//viewProj
//	mat4 ViewProj = proj * eyeToHeadTransform * headMat;
//	return ViewProj;
//}