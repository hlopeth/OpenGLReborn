#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
//#pragma comment(lib, "libname.lib")
#include "Shader.h"
#include "Camera.h"
#include "PointLight.h"
#include "Model.h"
#include "Material.h"
#include "Scene.h"
#include "VrRenderer.h"

using namespace std;
using namespace glm;
using namespace vr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initOpenGL();
void cleanUp();
void addCallbacks(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void draw();
void drawVR();
void genEyeTextures();
bool initOpenVR();
GLuint initVAO_container();
GLuint initVAO_lamp();
GLuint initVAO_plane();
void initShadowMap();
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//GLuint getTextureJPG(string img);
//GLuint getTexturePNG(string img);
mat4 getViewPosition(Hmd_Eye nEye);
vec3 getHeadPosition();


const GLuint SCR_WIDTH = 1024, SCR_HEIGHT = 1080;
//shadowMap
const GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
GLuint depthMapFBO;
GLuint depthMap;

glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)10000 / (float)10000, 0.1f, 100.0f);
float lastFrame = 0.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float cameraYaw=-90.0f, cameraPitch=0.0f;
GLuint screneFBO;
unsigned int quadVAO, quadVBO;
void initQuad();
ShaderProgram* screenSP = nullptr;
GLuint screenTexture;

vector<PointLight*> lights;
vector<Model*> actors;
Model* nanosuit;
Scene scene;

//openVR
vr::IVRSystem* vrSystem;

bool useVR=false;
GLuint leftEyeTexture=0, rightEyeTexture=0;
GLuint leftEyeFBO, rightEyeFBO;
VrRenderer vrRenderer(SCR_WIDTH, SCR_HEIGHT);
//float cameraOffsetX = 0, cameraOffsetY = 0, cameraOffsetZ = 0;

int main()
{
	GLFWwindow* window = initOpenGL();
	if (window == NULL)
		return -1;

	useVR = false;//= initOpenVR(); 
	//genEyeTextures();
	vrRenderer.Init();

	//frameBuffer
	initQuad();
	screenSP = new ShaderProgram("screenVertex.glsl", "screenFragment.glsl");
	glGenFramebuffers(1, &screneFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, screneFBO);
	// create a color attachment texture
	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Model nanosuitModel("assets/nanosuit/nanosuit.obj");
	ShaderProgram nanosuitSP("vertex.glsl", "fragment.glsl");
	Actor nanosuit(nanosuitModel, nanosuitSP, scale(mat4(1.0f),vec3(0.11f)));
	scene.actors.push_back(nanosuit);


	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera camera(cameraPos, cameraFront, cameraUp);
	scene.camera = camera;
	scene.projection = proj;


	glm::vec3 _white(1.0f);
	glm::vec3 _red(1.0f, 0.0f, 0.0f);
	glm::vec3 _green(0.0f, 1.0f, 0.0f);
	glm::vec3 _blue(0.0f, 0.0f, 1.0f);
	scene.pointLights.push_back(PointLight(vec3(0.0f, 0.0f, 10.0f), 0.3f*_white, _white, _white));
	scene.pointLights.push_back(PointLight(vec3(0.0f, 0.0f, -20.0f), 0.1f*_red, _red, _red));
	scene.pointLights.push_back(PointLight(vec3(10.0f, 0.0f, 0.0f), 0.1f*_green, _green, _green));
	scene.pointLights.push_back(PointLight(vec3(-10.0f, 0.0f, 0.0f), 0.1f*_blue, _blue, _blue));




	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//useVR ? drawVR() : draw();
		vrRenderer.Render(scene);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vrRenderer.Destroy();
	cleanUp();
	return 0;
}

void genEyeTextures()
{
	glGenFramebuffers(1, &leftEyeFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, leftEyeFBO);
	glGenTextures(1, &leftEyeTexture);
	glBindTexture(GL_TEXTURE_2D, leftEyeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, leftEyeTexture, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;


	glGenFramebuffers(1, &rightEyeFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, rightEyeFBO);

	glGenTextures(1, &rightEyeTexture);
	glBindTexture(GL_TEXTURE_2D, rightEyeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rightEyeTexture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool initOpenVR()
{
	vr::EVRInitError eError = vr::VRInitError_None;
	vrSystem = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		char buf[1024];
		sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		cout << buf << endl;
		return false;
	}

	eError = vr::VRInitError_None;

	if (!vr::VRCompositor())
	{
		printf("Compositor initialization failed. See log file for details\n");
		return false;
	}

	return true;
}

mat4 shadow_depth_view = lookAt(vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 0.0f, -1.0f));
float near_plane = 1.0f, far_plane = 40.5f;
glm::mat4 shadow_depth_proj = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, near_plane, far_plane);

void submitFramesOpenGL(GLuint leftEyeTex, GLuint rightEyeTex, bool linear = false)
{
	vr::TrackedDevicePose_t trackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	vr::VRCompositor()->WaitGetPoses(trackedDevicePose, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

	///\todo the documentation on this is completely unclear.  I have no idea which one is correct...
	/// seems to imply that we always want Gamma in opengl because linear is for framebuffers that have been
	/// processed by DXGI...

	vr::Texture_t leftEyeTexture  = { (void*)(uintptr_t)leftEyeTex,  vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
	vr::Texture_t rightEyeTexture = { (void*)(uintptr_t)rightEyeTex, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };

	vr::VRCompositorError error =  vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);
	vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);

	//vr::VRCompositor()->PostPresentHandoff();
}

void drawVR()
{
	mat4 contrMat = mat4(1.0f);
	for (unsigned int id = 0; id < k_unMaxTrackedDeviceCount; id++) {
		ETrackedDeviceClass trackedDeviceClass =
			vrSystem->GetTrackedDeviceClass(id);
		if (trackedDeviceClass != ETrackedDeviceClass::TrackedDeviceClass_Controller || !vrSystem->IsTrackedDeviceConnected(id))
			continue;

		//Confirmed that the device in question is a connected controller

		//This is all copied from above:
		TrackedDevicePose_t trackedDevicePose;
		VRControllerState_t controllerState;
		vrSystem->GetControllerStateWithPose(TrackingUniverseStanding, id, &controllerState, sizeof(controllerState), &trackedDevicePose);

		HmdMatrix34_t matPose = trackedDevicePose.mDeviceToAbsoluteTracking;

		 
		 vec3 x = normalize(vec3(matPose.m[0][0], matPose.m[1][0], matPose.m[2][0]));
		 vec3 y = normalize(vec3(matPose.m[0][1], matPose.m[1][1], matPose.m[2][1]));
		 vec3 z = normalize(vec3(matPose.m[0][2], matPose.m[1][2], matPose.m[2][2]));

		 contrMat = mat4(
			 x.x, x.y, x.z, 0.0f,
			 y.x, y.y, y.z, 0.0f,
			 z.x, z.y, z.z, 0.0f,
			 matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
		 );


		 //scene.actors[0].matrix = contrMat;
			
			
		//scene.actors[0].matrix = scale(scene.actors[0].matrix,vec3(0.03f));
	}


	vr::TrackedDevicePose_t trackedDevicePose_t[vr::k_unMaxTrackedDeviceCount];
	vr::VRCompositor()->WaitGetPoses(trackedDevicePose_t, vr::k_unMaxTrackedDeviceCount, nullptr, 0);
	vec3 headPos = getHeadPosition();

	//leftEye
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, leftEyeFBO);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mat4 viewProj = getViewPosition(Eye_Left);
	scene.Draw(viewProj,headPos);


	vr::Texture_t leftEyeTexture_t = { (void*)(uintptr_t)leftEyeTexture,  vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
	auto error = vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture_t);
	if(error != VRCompositorError_None) cout << "Left" << error<< endl;

	//rightEye
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, rightEyeFBO);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (false) { //eye in hand
		scene.camera.Pos = vec3(contrMat[3][0], contrMat[3][1], contrMat[3][2]);
		scene.camera.Up = vec3(contrMat[1][0], contrMat[1][1], contrMat[1][2]);
		scene.camera.Front = -vec3(contrMat[2][0], contrMat[2][1], contrMat[2][2]);
		scene.Draw();
	}
	else {
		viewProj = getViewPosition(Eye_Right);
		scene.Draw(viewProj, headPos);
	}

	vr::Texture_t rightEyeTexture_t = { (void*)(uintptr_t)rightEyeTexture, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
	error = vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture_t);
	if (error != VRCompositorError_None) cout << "Right" << error << endl;

	//submitFramesOpenGL(leftEyeTexture, rightEyeTexture);

	//screeFBO
	glBindFramebuffer(GL_FRAMEBUFFER, screneFBO);
	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.Draw();

	

	//screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, SCR_WIDTH/2, SCR_HEIGHT);
	screenSP->use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, leftEyeTexture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glViewport(SCR_WIDTH/2, 0, SCR_WIDTH/2, SCR_HEIGHT);
	screenSP->use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, rightEyeTexture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);



}

void draw()
{

	/*glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	renderScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	scene.Draw();
	renderScene();*/

	glBindFramebuffer(GL_FRAMEBUFFER, screneFBO);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.Draw();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
	screenSP->use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, screenTexture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLFWwindow* initOpenGL()
{
	if (!glfwInit())
	{
		cout << "Failed to init GLFW" << endl;
		return NULL;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//buff for antyaliasing MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Reborn", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return NULL;
	}

	int count;
	const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	initShadowMap();

	addCallbacks(window);

	return window;
}

void initShadowMap()
{
	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//может линеар?
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void cleanUp()
{
	vr::VR_Shutdown();
	//delete(camera);
	/*delete(containerModel);
	delete(lampModel);*/
	for(PointLight* light: lights)
		delete(light);
	for (Model* actor : actors)
		delete(actor);
	glfwTerminate();
}

GLuint initVAO_container()
{
	GLfloat vertices[] = {
	//pos______________   tex_coord_   normal____________
	-1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

	-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

	 1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
	 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
	 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
	 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
	 1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,

	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
	 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
	 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
	 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
	-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	};
	GLuint indices[] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36
	};

	//VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	int step = 8;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return VAO;
}

GLuint initVAO_lamp()
{
	GLfloat vertices[] = {
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
					   
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
					   
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
					   
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
					   
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
					   
	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f
	};
	GLuint indices[] = {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36
	};

	//VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return VAO;
}

GLuint initVAO_plane()
{
	GLfloat vertices[] = {
		//pos______________   tex_coord_	normal____________
		 1.0f, 0.0f,  1.0f,   1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f,  1.0f,   0.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		 1.0f, 0.0f, -1.0f,   1.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, -1.0f,   0.0f, 0.0f,	0.0f, 1.0f, 0.0f
	};
	GLuint indices[] = {
		0,1,2, 1,2,3
	};

	//VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	int step = 8;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, step * sizeof(GLfloat), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return VAO;
}
/*
GLuint getTextureJPG(string img)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(img.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture " << img << std::endl;
	}
	stbi_image_free(data);

	return texture;
}

GLuint getTexturePNG(string img)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(img.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture " << img << std::endl;
	}
	stbi_image_free(data);

	return texture;
}
*/
void addCallbacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void processInput(GLFWwindow *window)
{
	float currentFrame = glfwGetTime();
	float cameraSpeed = 10.0f * (currentFrame - lastFrame);
	lastFrame = currentFrame;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		scene.camera.Pos += cameraSpeed * scene.camera.Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene.camera.Pos -= cameraSpeed * scene.camera.Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene.camera.Pos -= scene.camera.Right() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene.camera.Pos += scene.camera.Right() * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cameraYaw += xoffset;
	cameraPitch += yoffset;

	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	front.y = sin(glm::radians(cameraPitch));
	front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
	scene.camera.Front = glm::normalize(front);
}

void initQuad()
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

mat4 getViewPosition(Hmd_Eye nEye)
{
	//proj
	vr::HmdMatrix44_t mat = vrSystem->GetProjectionMatrix(nEye, 0.1f, 100.0f);
	mat4 proj(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);

	//eye to head transform
	vr::HmdMatrix34_t mat34 = vrSystem->GetEyeToHeadTransform(nEye);
	mat4 matrix_eyeToHead(
		mat34.m[0][0], mat34.m[1][0], mat34.m[2][0], 0.0,
		mat34.m[0][1], mat34.m[1][1], mat34.m[2][1], 0.0,
		mat34.m[0][2], mat34.m[1][2], mat34.m[2][2], 0.0,
		mat34.m[0][3], mat34.m[1][3], mat34.m[2][3], 1.0f
	);
	mat4 eyeToHeadTransform = glm::inverse(matrix_eyeToHead);

	//head
	TrackedDevicePose_t trackedDevicePose;
	vrSystem->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, 0, &trackedDevicePose, 1);
	mat34 = trackedDevicePose.mDeviceToAbsoluteTracking;
	mat4 matrix_head(
		mat34.m[0][0], mat34.m[1][0], mat34.m[2][0], 0.0,
		mat34.m[0][1], mat34.m[1][1], mat34.m[2][1], 0.0,
		mat34.m[0][2], mat34.m[1][2], mat34.m[2][2], 0.0,
		mat34.m[0][3], mat34.m[1][3], mat34.m[2][3], 1.0f
	);
	mat4 headMat = glm::inverse(matrix_head);

	//viewProj
	mat4 ViewProj = proj * eyeToHeadTransform * headMat;
	return ViewProj;
}

vec3 getHeadPosition()
{
	TrackedDevicePose_t trackedDevicePose;
	vrSystem->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, 0, &trackedDevicePose, 1);
	HmdMatrix34_t mat34 = trackedDevicePose.mDeviceToAbsoluteTracking;
	vec3 head_pos(mat34.m[0][3],	mat34.m[1][3],	mat34.m[2][3]);

	return head_pos;
}