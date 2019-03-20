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

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "PointLight.h"
#include "Actor.h"

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initOpenGL();
void cleanUp();
void addCallbacks(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void draw();
GLuint initVAO_container();
GLuint initVAO_lamp();
GLuint initVAO_plane();
void renderScene(mat4 view, mat4 proj);
void initShadowMap();
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
GLuint getTextureJPG(string img);
GLuint getTexturePNG(string img);


const GLuint SCR_WIDTH = 1024, SCR_HEIGHT = 1080;
//shadowMap
const GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
GLuint depthMapFBO;
GLuint depthMap;

glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)10000 / (float)10000, 0.1f, 100.0f);
Camera* camera;
float lastFrame = 0.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float cameraYaw=-90.0f, cameraPitch=0.0f;

Model* containerModel;
Model* lampModel;
Model* planeModel;
vector<PointLight*> lights;
vector<Actor*> actors;
Actor* nanosuit;

int main()
{
	GLFWwindow* window = initOpenGL();
	if (window == NULL)
		return -1;

	//plmeModel
	Material materialPlane(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.2f), 1);
	ShaderProgram shaderProgramPlane("planeVertex.glsl", "planeFragment.glsl");
	GLuint planeTexture = getTextureJPG("texture/soil_ground.jpg");
	planeModel = new Model(initVAO_plane(), shaderProgramPlane, 6, vector<GLuint> {planeTexture, depthMap}, materialPlane);

	//containerModel
	GLuint VAO = initVAO_container();	
	ShaderProgram shaderProgram("vertex.glsl", "fragment.glsl");
	GLuint texture = getTexturePNG("texture/container2.png");
	GLuint spec_map = getTexturePNG("texture/container2_specular.png");
	Material material(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32);
	containerModel = new Model(VAO, shaderProgram, 36, vector<GLuint> { texture, spec_map }, material);

	//lampModel
	ShaderProgram shaderProgramLight("lampVertex.glsl", "lampFragment.glsl");
	Material lampMaterial;
	lampModel = new Model(initVAO_lamp(), shaderProgramLight, 64);

	//lampModel
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	camera = new Camera(cameraPos, cameraFront, cameraUp);


	//lights
	glm::vec3 white(1.0f);
	glm::vec3 red(1.0f, 0.0f, 0.0f);
	glm::vec3 green(0.0f, 1.0f, 0.0f);
	glm::vec3 blue(0.0f, 0.0f, 1.0f);
	lights.push_back(new PointLight(vec3(  0.0f, 0.0f, 10.0f), 0.3f*white, white, white));
	lights.push_back(new PointLight(vec3(  0.0f, 0.0f,-20.0f), 0.1f*red, red, red));
	lights.push_back(new PointLight(vec3( 10.0f, 0.0f,  0.0f), 0.1f*green, green, green));
	lights.push_back(new PointLight(vec3(-10.0f, 0.0f,  0.0f), 0.1f*blue, blue, blue));
	
	//nanosiut
	nanosuit = new Actor("assets/nanosuit/nanosuit.obj");


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	cleanUp();
	return 0;
}

mat4 shadow_depth_view = lookAt(vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 0.0f, -1.0f));
float near_plane = 1.0f, far_plane = 40.5f;
glm::mat4 shadow_depth_proj = glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, near_plane, far_plane);

void draw()
{
	glm::mat4 view = camera->getMatrix();

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	renderScene(shadow_depth_view, proj);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	renderScene(view, proj);


}

void renderScene(mat4 view, mat4 proj)
{
	//plane
	planeModel->use();
	mat4 m_model1 = glm::translate(mat4(1.0f), vec3(0.0f, -7.0f, -10.0f));
	m_model1 = scale(m_model1, vec3(25.0f)); 
	planeModel->shaderProgram.setUniform("texture_diffuse1", 0);
	planeModel->shaderProgram.setUniform("depthMap", 1);
	planeModel->shaderProgram.setUniform("n_pointLights", (int)lights.size());
	for (int i = 0; i < lights.size(); i++)
	{
		char ch_i = '0' + i;
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].position", lights[i]->position);
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].ambient", lights[i]->ambient);
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].diffuse", lights[i]->diffuse);
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].specular", lights[i]->specular);
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].constant", lights[i]->constant);
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].linear", lights[i]->linear);
		planeModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].quadratic", lights[i]->quadratic);
	}
	planeModel->shaderProgram.setUniform("cameraPos", camera->Pos);
	planeModel->shaderProgram.setUniform("mvp", proj * view * m_model1);
	planeModel->shaderProgram.setUniform("model", m_model1);
	planeModel->shaderProgram.setUniform("lightSpaceMat", proj*shadow_depth_view);
	planeModel->draw();



	containerModel->use();
	containerModel->shaderProgram.setUniform("texture_diffuse1", 0);
	containerModel->shaderProgram.setUniform("texture_specular1", 1);
	containerModel->shaderProgram.setUniform("n_pointLights", (int)lights.size());
	for (int i = 0; i < lights.size(); i++)
	{
		char ch_i = '0' + i;
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].position", lights[i]->position);
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].ambient", lights[i]->ambient);
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].diffuse", lights[i]->diffuse);
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].specular", lights[i]->specular);
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].constant", lights[i]->constant);
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].linear", lights[i]->linear);
		containerModel->shaderProgram.setUniform(string("pointLights[") + ch_i + "].quadratic", lights[i]->quadratic);
	}
	containerModel->shaderProgram.setUniform("cameraPos", camera->Pos);

	glm::mat4 m_model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -10.0f));
	glm::mat4 mvp = proj * view * m_model;
	containerModel->shaderProgram.setUniform("mvp", mvp);
	containerModel->shaderProgram.setUniform("model", m_model);
	containerModel->draw();

	m_model = glm::translate(glm::mat4(1.0), glm::vec3(-7.0f, -5.0f, -8.0f));
	m_model = glm::rotate(m_model, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	containerModel->shaderProgram.setUniform("mvp", proj * view * m_model);
	containerModel->shaderProgram.setUniform("model", m_model);
	containerModel->draw();


	m_model = glm::translate(glm::mat4(1.0), glm::vec3(5.0f, 0.0f, -15.0f));
	m_model = glm::rotate(m_model, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	containerModel->shaderProgram.setUniform("mvp", proj * view * m_model);
	containerModel->shaderProgram.setUniform("model", m_model);
	containerModel->draw();


	m_model = glm::translate(glm::mat4(1.0), glm::vec3(2.0f, 5.0f, -9.0f));
	m_model = glm::rotate(m_model, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	containerModel->shaderProgram.setUniform("mvp", proj * view * m_model);
	containerModel->shaderProgram.setUniform("model", m_model);
	containerModel->draw();


	m_model = glm::translate(glm::mat4(1.0), glm::vec3(-5.0f, 9.0f, -20.0f));
	m_model = glm::rotate(m_model, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	containerModel->shaderProgram.setUniform("mvp", proj * view * m_model);
	containerModel->shaderProgram.setUniform("model", m_model);
	containerModel->draw();


	m_model = glm::translate(glm::mat4(1.0), glm::vec3(5.0f, -3.0f, -5.0f));
	m_model = glm::rotate(m_model, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	containerModel->shaderProgram.setUniform("mvp", proj * view * m_model);
	containerModel->shaderProgram.setUniform("model", m_model);
	containerModel->draw();


	//lamps
	for (int i = 0; i < lights.size(); i++)
	{
		m_model = glm::translate(glm::mat4(1.0), lights[i]->position);
		m_model = glm::scale(m_model, glm::vec3(0.2f));
		mvp = proj * view * m_model;
		lampModel->use();
		lampModel->shaderProgram.setUniform("mvp", mvp);
		lampModel->shaderProgram.setUniform("lampColor", lights[i]->diffuse);
		lampModel->draw();
	}
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
	delete(camera);
	delete(containerModel);
	delete(lampModel);
	for(PointLight* light: lights)
		delete(light);
	for (Actor* actor : actors)
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
		camera->Pos += cameraSpeed * camera->Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->Pos -= cameraSpeed * camera->Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->Pos -= camera->Right() * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->Pos += camera->Right() * cameraSpeed;
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

	float sensitivity = 0.1;
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
	camera->Front = glm::normalize(front);
}