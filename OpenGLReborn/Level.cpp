#include "Level.h"
#include "MouseClickEvent.h"
#include "ResizeEvent.h"
#include "ExitEvent.h"
#include "Triangle.h"
#include "Nanosuit.h"
#include "UIRect.h"
#include "Button.h"
#include "Box.h"
#include "VerticalLayout.h"
#include "UIRoot.h"
#include "Lamp.h"
#include "MainMenu.h"
#include "Trace.h"
#include "Event.h"
#include "Plane.h"
#include "BoxPhysicsShape.h"
#include "SkyBox.h"
#include "Terrain.h"
#include "MeshPrimitives.h"
#include "DirectinalLight.h"
#include "HeightfieldPhysicsBody.h"
#include "TextureFromFile.h"
#include "SingleTextureMaterial.h"
#include "RendererManager.h"
#include "PhysicsManager.h"

SkyBox* createScyBox() 
{
	auto left	= TextureFromFile("left.png",	"assets/skybox");
	auto right	= TextureFromFile("right.png",	"assets/skybox");
	auto top	= TextureFromFile("top.png",	"assets/skybox");
	auto bottom = TextureFromFile("bottom.png", "assets/skybox");
	auto front	= TextureFromFile("front.png",	"assets/skybox");
	auto back	= TextureFromFile("back.png",	"assets/skybox");
	CubeTexture cubeTexture(
		left,
		right,
		top,
		bottom,
		front,
		back
	);
	return new SkyBox(cubeTexture);
}

shared_ptr<SingleTextureMaterial> createSingleTextureMaterial()
{
	Texture boxTexture = TextureFromFile("box.png", "assets");
	GLTexture boxGLTexture = GLTexture(boxTexture, GL_RGBA);
	return make_shared<SingleTextureMaterial>(boxGLTexture, vec3(1.0));
}

void setupUI(UIRoot& uiRoot)
{
	Canvas& c = uiRoot.getCanvas();
	UI::MainMenu* mainMenu = new UI::MainMenu();
	mainMenu->visible = false;
	c.addChild(mainMenu);
}

Level::Level():
	camera(vec3(0.0), vec3(0.0), vec3(0.0))
{
	setupUI(uiRoot);

	auto singleTextureMaterial = createSingleTextureMaterial();

	DirectinalLight* dirLight = new DirectinalLight(vec3(0.0, 0.0, 1.0), vec3(1.0, 1.0, 1.0));
	//������� ���� �������� ����� � ������������
	Nanosuit* nanosuit = new Nanosuit();
	nanosuit->physicsBody = new BoxPhysicsShape(vec3(1.0), *nanosuit, 0.f);
	Lamp* lampWhite = new Lamp();
	lampWhite->pointLight.diffuse = vec3(0.8);
	Lamp* lampRed = new Lamp();
	lampRed->setPosition(vec3(0.0, 15.0, -5.0));
	lampRed->pointLight.diffuse = vec3(0.8, 0.1, 0.1);
	Lamp* lampBlue = new Lamp();		
	lampBlue->setPosition(vec3(0.0, 15.0, 5.0));
	lampBlue->pointLight.diffuse = vec3(0.1, 0.1, 0.8);
	/*Plane* plane = new Plane();
	plane->setPosition(vec3(0.0, -5.0, 0.0));
	plane->setScale(vec3(50.f, 0.01f, 50.f));
	plane->physicsBody = new BoxPhysicsShape(vec3(1.0),*plane, 0.f);*/

	for (int i = -5; i < 5; i++) {
		for (int j = -5; j < 5; j++) {
			if (i == 0 && j == 0) continue;
			Box* box = new Box(singleTextureMaterial);
			box->selectable = true;
			const float scale = 5;
			box->setPosition(vec3(i * scale, 20.f, j * scale));
			box->physicsBody = new BoxPhysicsShape(vec3(1.0), *box, 1.f);
			box->physicsBody->copyTransform(*box);
			scene.addGameObject(box);
		}
	}
	
	SkyBox *skyBox = createScyBox();

	Texture heightMap = TextureFromFile("heightmap.png", "assets/terrane");
	GLTexture terrainTexture = GLTexture(
		TextureFromFile("grass.png", "assets/terrane"),
		GL_RGB,
		GL_MIRRORED_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR
	);
	Terrain* terrain = new Terrain(heightMap, terrainTexture);
	terrain->setPosition(vec3(0.0, -90.0, 0.0));
	terrain->setScale(vec3(1.f, 1.f, 1.f));
	terrain->physicsBody = new HeightfieldPhysicsBody(heightMap, *terrain, 0.f);

	
	scene.setDirectinalLight(dirLight);
	scene.setSkyBox(skyBox);
	scene.addGameObject(nanosuit);
	scene.addGameObject(lampWhite);
	scene.addGameObject(lampRed);
	scene.addGameObject(lampBlue);
//	scene.addGameObject(plane);
	scene.addGameObject(terrain);
	scene.addPointLight(&(lampWhite->pointLight));
	scene.addPointLight(&(lampRed->pointLight));
	scene.addPointLight(&(lampBlue->pointLight));

	camera.pos = glm::vec3(0.0f, 0.0f, 10.0f);
	camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->setEventHandler<Level, KeyEvent>(this, &Level::onKey);
	this->setEventHandler<Level, ExitEvent>(this, &Level::onExit);

}

void Level::update(double gameTime, double deltaTime)
{
	camera.update(gameTime, deltaTime);
}

Camera& Level::getCamera()
{
	return camera;
}

Scene& Level::getScene()
{
	return scene;
}

UIRoot& Level::getUIRoot()
{
	return uiRoot;
}

void Level::afterPhysicsUpdate()
{
	vec3 hitPoint;
	vec3 hitNormal;
	AbstractPhysicsBody* body = nullptr;
	if (PHYSICS.rayCast(camera.pos, camera.pos + camera.front * vec3(1000.0), hitPoint, hitNormal, body))
	{
		if (body != nullptr )
		{
			if (body->gameObject().selectable)
			{
				if (auto model = dynamic_cast<Model*>(&(body->gameObject())))
				{
					selectedModel = model;
				}
				else
				{
					selectedModel = nullptr;
				}
			}
			else
			{
				selectedModel = nullptr;
			}
		}
		else 
		{
			selectedModel = nullptr;
		}
	}
	else
	{
		selectedModel = nullptr;
	}


	auto gameObjects = scene.getGameObjects();
	for (auto gameObject : gameObjects) {
		gameObject->afterPhysicsUpdate();
	}
}

void Level::onKey(const KeyEvent& event)
{
	if (event.key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(&WINDOW, true);
	}
}

void Level::onExit(const ExitEvent& event)
{
	glfwSetWindowShouldClose(&WINDOW, true);
}

void Level::call(const Event& event)
{
	EventComponent::call(event);
	camera.call(event);
	uiRoot.call(event);
}
