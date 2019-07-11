#include "Scene.h"

void Scene::Draw()
{
	for (Actor actor : actors)
	{
		ShaderProgram shader = actor.shader;
		shader.use();
		shader.setUniform("n_pointLights", (int)pointLights.size());
		for (unsigned int i = 0; i < pointLights.size(); i++)
		{
			char ch_i = '0' + i;
			shader.setUniform(string("pointLights[") + ch_i + "].position", pointLights[i].position);
			shader.setUniform(string("pointLights[") + ch_i + "].ambient", pointLights[i].ambient);
			shader.setUniform(string("pointLights[") + ch_i + "].diffuse", pointLights[i].diffuse);
			shader.setUniform(string("pointLights[") + ch_i + "].specular", pointLights[i].specular);
			shader.setUniform(string("pointLights[") + ch_i + "].constant", pointLights[i].constant);
			shader.setUniform(string("pointLights[") + ch_i + "].linear", pointLights[i].linear);
			shader.setUniform(string("pointLights[") + ch_i + "].quadratic", pointLights[i].quadratic);
			if (i == 0) {
				unsigned int textureUnit = 3 + i;
				glActiveTexture(GL_TEXTURE0 + textureUnit);
				glBindTexture(GL_TEXTURE_CUBE_MAP, pointLights[i].shadowCubeMap);
				shader.setUniform(string("shadowCubeMaps[") + ch_i + "]", textureUnit);
			}
			//shader.setUniform(string("shadowCubeMap") + ch_i, 3 + i);
			shader.setUniform(string("pointLights[") + ch_i + "].farPlane", pointLights[i].farPlane);
		}
		shader.setUniform("cameraPos", camera.Pos);
		actor.Draw(projection*camera.getMatrix());
	}
}

void Scene::Draw(mat4 matr, vec3 pos)
{
	for (Actor actor : actors)
	{
		ShaderProgram shader = actor.shader;
		shader.use();
		shader.setUniform("n_pointLights", (int)pointLights.size());
		for (unsigned int i = 0; i < pointLights.size(); i++)
		{
			char ch_i = '0' + i;
			shader.setUniform(string("pointLights[") + ch_i + "].position", pointLights[i].position);
			shader.setUniform(string("pointLights[") + ch_i + "].ambient", pointLights[i].ambient);
			shader.setUniform(string("pointLights[") + ch_i + "].diffuse", pointLights[i].diffuse);
			shader.setUniform(string("pointLights[") + ch_i + "].specular", pointLights[i].specular);
			shader.setUniform(string("pointLights[") + ch_i + "].constant", pointLights[i].constant);
			shader.setUniform(string("pointLights[") + ch_i + "].linear", pointLights[i].linear);
			shader.setUniform(string("pointLights[") + ch_i + "].quadratic", pointLights[i].quadratic);
		}
		shader.setUniform("cameraPos", pos);
		actor.Draw(matr);
	}
}