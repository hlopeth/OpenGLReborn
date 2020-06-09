#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;

	Vertex() {};
	Vertex(glm::vec3 _Position, glm::vec2 _TexCoord, glm::vec3 _Normal) :
		Position(_Position), TexCoords(_TexCoord), Normal(_Normal) {};
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh {
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	glm::vec3 color;
	/*  Functions  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, glm::vec3 color);
	void Draw(ShaderProgram& shader);
private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();
};