#include "Level.h"
#include <future>
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
#include "DirectionalLight.h"
#include "HeightfieldPhysicsBody.h"
#include "TextureFromFile.h"
#include "SingleTextureMaterial.h"
#include "RendererManager.h"
#include "PhysicsManager.h"
#include "TerrainMaterial.h"
#include "Water.h"

SkyBox* createSkyBox() 
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

Terrain* loadTerrain(const string& filename, shared_ptr<TerrainMaterial> material, int i, int j)
{
	Texture heightMap = TextureFromFile(filename.c_str(), "assets/terrain");
	Terrain* terrain = new Terrain(heightMap, material);
	float offset = terrain->getHightestPoint() - (terrain->getHightestPoint() - terrain->getLowestPoint()) / 2.0;
	float scale = 1.0;
	terrain->setPosition(vec3(i * scale *(heightMap.height - 1), offset - 100.0, j * scale *(heightMap.width - 1)));
	terrain->setScale(vec3(scale, 1.0, scale));
	terrain->physicsBody = new HeightfieldPhysicsBody(heightMap, *terrain, 0.f);
	return terrain;
}

Level::Level():
	camera(vec3(0.0), vec3(0.0), vec3(0.0))
{
	setupUI(uiRoot);

	auto singleTextureMaterial = createSingleTextureMaterial();

	DirectionalLight* dirLight = new DirectionalLight(glm::normalize(vec3(0.0, 1.0, 1.0)), vec3(1.0, 1.0, 1.0));
	//уровень пока строится прямо в конструкторе
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
			box->physicsBody = new BoxPhysicsShape(vec3(1.0), *box, 0.f);
			box->physicsBody->copyTransform(*box);
			scene.addGameObject(box);
		}
	}
	
	SkyBox *skyBox = createSkyBox();

	//Terrain
	GLTexture sandTexture = GLTexture(
		TextureFromFile("sand.png", "assets/terrain"),
		GL_RGB,
		GL_MIRRORED_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR
	);
	GLTexture grassTexture = GLTexture(
		TextureFromFile("grass.png", "assets/terrain"),
		GL_RGB,
		GL_MIRRORED_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR
	);
	GLTexture rockTexture = GLTexture(
		TextureFromFile("rock.png", "assets/terrain"),
		GL_RGB,
		GL_MIRRORED_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_LINEAR
	);
	shared_ptr<TerrainMaterial> terrainMaterial = make_shared<TerrainMaterial>(sandTexture, grassTexture, rockTexture);
	int k = 1;
	std::vector<std::future<Terrain*>> terrains;
	for (int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			string filename = "out" + to_string(k) + ".png";
			terrains.push_back(std::async(loadTerrain, filename, terrainMaterial, i, j));
			k++;
		}

	for (int i = 0; i < terrains.size(); i++)
	{
		terrains[i].wait();
		scene.addGameObject(terrains[i].get());
	}

	//Water
	shared_ptr<WaterMaterial> waterMaterial = make_shared<WaterMaterial>(glm::vec4(0, 0.467, 0.745, 0.8));
	//513 - размер heightmap
	Water* water = new Water(513, 513, waterMaterial);
	water->setPosition(vec3(-256.5, -90.5, -256.5));
	water->setScale(vec3(4.0, 1.0, 4.0));
	
	scene.setDirectionalLight(dirLight);
	scene.setSkyBox(skyBox);
	scene.addGameObject(nanosuit);
	scene.addGameObject(lampWhite);
	scene.addGameObject(lampRed);
	scene.addGameObject(lampBlue);
//	scene.addGameObject(plane);
	scene.addPointLight(&(lampWhite->pointLight));
	scene.addPointLight(&(lampRed->pointLight));
	scene.addPointLight(&(lampBlue->pointLight));
	//water в конце из за прозрачности
	scene.addGameObject(water);

	camera.pos = glm::vec3(0.0f, 0.0f, 10.0f);
	camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->setEventHandler<Level, KeyEvent>(this, &Level::onKey);
	this->setEventHandler<Level, ExitEvent>(this, &Level::onExit);

}

void Level::update(double gameTime, double deltaTime)
{
	camera.update(gameTime, deltaTime);
	for (auto gameObject : scene.getGameObjects())
	{
		gameObject->update(gameTime, deltaTime);
	}
}

Camera& Level::getCamera()
{
	return camera;
}

const Camera& Level::getCamera() const
{
	return camera;
}

Scene& Level::getScene()
{
	return scene;
}

const Scene& Level::getScene() const
{
	return scene;
}

const UIRoot& Level::getUIRoot() const
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
	if (event.key == GLFW_KEY_F)
	{
		if (selectedModel != nullptr)
		{
			selectedModel->call(SelectEvent());
		}
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
	for (auto gameObject: scene.getGameObjects())
	{
		gameObject->call(event);
	}
	uiRoot.call(event);
}
