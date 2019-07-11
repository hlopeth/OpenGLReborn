#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

struct PointLight
{
	const GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant=1.0f;
	float linear=0.1f;
	float quadratic=0.02f;

	GLuint shadowFBO;
	GLuint shadowCubeMap;
	float farPlane = 25.0f;

	PointLight()
	{
		position = vec3(0.0f);
		ambient  = vec3(0.0f);
		diffuse  = vec3(0.0f);
		specular = vec3(0.0f);

		glGenFramebuffers(1, &shadowFBO);
		glGenTextures(1, &shadowCubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, shadowCubeMap);
		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowCubeMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	PointLight(vec3 position) :PointLight()
	{
		this->position = position;
		ambient = vec3(1.0f);
		diffuse = vec3(1.0f);
		specular = vec3(1.0f);
	}
	PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular) : PointLight()
	{
		this->position = position;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}

};