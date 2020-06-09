#pragma once
#include "Mesh.h"

namespace RenderingPrimitives
{
	Mesh Box(vector<Texture> textures, glm::vec3 color);
	Mesh Plane(vector<Texture> textures, glm::vec3 color);
	Texture DefaultTexture();
}