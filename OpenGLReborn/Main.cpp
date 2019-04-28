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
void GenFramebuffer();
void Draw();
void cleanUp();
void addCallbacks(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLuint initVAO_container();
GLuint initVAO_lamp();
GLuint initVAO_plane();
void initShadowMap();
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


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
unsigned int quadVAO, quadVBO;
void initQuad();
ShaderProgram* screenSP = nullptr;
GLuint screenFBO, screenRBO;
GLuint screenTexture;

vector<PointLight*> lights;
vector<Model*> actors;
Model* nanosuit;
Scene scene;

//openVR
VrRenderer vrRenderer(SCR_WIDTH, SCR_HEIGHT);

int main()
{
	GLFWwindow* window = initOpenGL();
	if (window == NULL)
		return -1;

	vrRenderer.Init();

	//frameBuffer
	initQuad();
	screenSP = new ShaderProgram("screenVertex.glsl", "screenFragment.glsl");


	GenFramebuffer();

	/*Model nanosuitModel("assets/nanosuit/nanosuit.obj");
	ShaderProgram nanosuitSP("vertex.glsl", "fragment.glsl");
	Actor nanosuit(nanosuitModel, nanosuitSP, scale(mat4(1.0f),vec3(0.11f)));
	scene.actors.push_back(nanosuit);*/

	Model drum_setModel("assets/lowpoly_forest_bl/lowpoly_forest.obj");
	ShaderProgram drum_setSP("vertex.glsl", "fragment.glsl");
	Actor drum_set(drum_setModel, drum_setSP, scale(mat4(1.0f), vec3(0.11f)));
	scene.actors.push_back(drum_set);


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
	scene.pointLights.push_back(PointLight(vec3( 0.0f, 8.0f, 0.0f), 0.8f*_white, _white, _white));
	//scene.pointLights.push_back(PointLight(vec3( 0.0f, 8.0f, 5.0f), 0.2f*_white, _white, _white));
	//scene.pointLights.push_back(PointLight(vec3( 0.0f, 8.0f,-5.0f), 0.2f*_white, _white, _white));
	//scene.pointLights.push_back(PointLight(vec3(-10.0f, 0.0f, 0.0f), 0.1f*_blue, _blue, _blue));




	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		vrRenderer.Render(scene);
		Draw();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vrRenderer.Destroy();
	cleanUp();
	return 0;
}

void Draw()
{
	glEnable(GL_DEPTH_TEST);
	//screeFBO
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.Draw();

	//screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	screenSP->use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, screenTexture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GenFramebuffer()
{
	glGenFramebuffers(1, &screenFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
	// create a color attachment texture
	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	glGenRenderbuffers(1, &screenRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, screenRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, screenRBO); // now actually attach it
																										// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, screenRBO);
}

mat4 shadow_depth_view = lookAt(vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 0.0f, -1.0f));
float near_plane = 1.0f, far_plane = 40.5f;
glm::mat4 shadow_depth_proj = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, near_plane, far_plane);


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
