#pragma once
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "GLTexture.h"
#include "AABB.h"

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangents;
	glm::vec3 Bitangents;
};


class Mesh {
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<GLTexture> diffuseTextures;
	vector<GLTexture> ambientTextures;
	vector<GLTexture> emissiveTextures;
	vector<GLTexture> specularTextures;
	vector<GLTexture> normalTextures;
	glm::vec3 color;
	/*  Functions  */
	Mesh(
		vector<Vertex> vertices, 
		vector<unsigned int> indices,
		glm::vec3 color,
		vector<GLTexture> diffuseTextures = {},
		vector<GLTexture> ambientTextures = {},
		vector<GLTexture> emissiveTextures = {},
		vector<GLTexture> specularTextures = {},
		vector<GLTexture> normalTextures = {}
	);
	void Draw(ShaderProgram& shader);
	const AABB& GetAABB();
private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();
	AABB aabb;
};