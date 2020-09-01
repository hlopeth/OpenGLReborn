#pragma once
//#include "Actor.h"
//#include "PointLight.h"
//#include "Camera.h"
//#include "DirectinalLight.h"
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//using namespace std;

//struct Scene
//{
//	vector<Actor> actors;
//	vector<PointLight> pointLights;
//	DirectinalLight directinalLight;
//	Camera camera;
//	glm::mat4 projection;
//	GLuint shadowMaps;
//	
//	Scene() {};
//
//	void Draw();
//
//	void Draw(mat4 matr, vec3 pos);
//
//};

#include <vector>
#include "GameObject.h"
#include "PointLight.h"

#define MAX_POINT_LIGHTS 16

using std::vector;

class Scene
{
public:
	vector<GameObject*>& getGameObjects();
	vector<PointLight*>& getPointLights();
	void addGameObject(GameObject* gameObject);
	bool addPointLight(PointLight* pointLight);

	//DirectinalLight* directinalLight;
private:
	vector<GameObject*> gameObjects;
	vector<PointLight*> pointLights;
};