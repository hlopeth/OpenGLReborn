#include "MeshPrimitives.h"

const vector<Vertex> boxVertices{
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),
																			 
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),

	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f)),

	Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f)),
																			 
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),
																			 
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f)),
	Vertex(glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3( 0.0f,  1.0f,  0.0f))
};

const vector<unsigned int> boxIndices {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36
};

Mesh MeshPrimitives::Box(vector<Texture> textures, glm::vec3 color)
{
	return Mesh(boxVertices, boxIndices, textures, color);
}
