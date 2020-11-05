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
	/*  Functions  */
	Mesh();
	Mesh(const Mesh& mesh);
	Mesh(
		vector<Vertex> vertices, 
		vector<unsigned int> indices
	);

	const AABB& getAABB() const;
	GLuint getVAO() const;
	GLuint getVBO() const;
	GLuint getEBO() const;
private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;
	AABB aabb;
	/*  Functions    */
	void setupMesh();
};