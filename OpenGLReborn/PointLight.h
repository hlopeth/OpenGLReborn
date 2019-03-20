#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;


	float constant=1.0f;
	float linear=0.1f;
	float quadratic=0.02f;

	PointLight()
	{
		position = vec3(0.0f);
		ambient  = vec3(0.0f);
		diffuse  = vec3(0.0f);
		specular = vec3(0.0f);
	}

	PointLight(vec3 position)
	{
		this->position = position;
		ambient = vec3(1.0f);
		diffuse = vec3(1.0f);
		specular = vec3(1.0f);
	}
	PointLight(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular)
	{
		this->position = position;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}

};