#pragma once
#include "Actor.h"
#include "PointLight.h"
#include "Camera.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Scene
{
	vector<Actor> actors;
	vector<PointLight> pointLights;
	Camera camera;
	glm::mat4 projection;

	Scene()	{}

	void Draw()
	{
		for (Actor actor : actors)
		{
			ShaderProgram shader = actor.shader;
			shader.use();
			shader.setUniform("n_pointLights", (int)pointLights.size());
			for (int i = 0; i < pointLights.size(); i++)
			{
				char ch_i = '0' + i;
				shader.setUniform(string("pointLights[") + ch_i + "].position",  pointLights[i].position);
				shader.setUniform(string("pointLights[") + ch_i + "].ambient",   pointLights[i].ambient);
				shader.setUniform(string("pointLights[") + ch_i + "].diffuse",   pointLights[i].diffuse);
				shader.setUniform(string("pointLights[") + ch_i + "].specular",  pointLights[i].specular);
				shader.setUniform(string("pointLights[") + ch_i + "].constant",  pointLights[i].constant);
				shader.setUniform(string("pointLights[") + ch_i + "].linear",    pointLights[i].linear);
				shader.setUniform(string("pointLights[") + ch_i + "].quadratic", pointLights[i].quadratic);
			}
			shader.setUniform("cameraPos", camera.Pos);
			actor.Draw(projection*camera.getMatrix());
		}
	}

};