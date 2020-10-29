#include "Mesh.h"
#include <algorithm>

Mesh::Mesh(
	vector<Vertex> vertices,
	vector<unsigned int> indices,
	glm::vec3 color,
	vector<GLTexture> diffuseTextures,
	vector<GLTexture> ambientTextures,
	vector<GLTexture> emissiveTextures,
	vector<GLTexture> specularTextures
) {
	this->vertices = vertices;
	this->indices = indices;
	this->diffuseTextures = diffuseTextures;
	this->ambientTextures = ambientTextures;
	this->emissiveTextures = emissiveTextures;
	this->specularTextures = specularTextures;
	this->color = color;
	setupMesh();
}

void Mesh::setupMesh()
{
	float maxY = vertices[0].Position.y;
	float minY = vertices[0].Position.y;
	float maxX = vertices[0].Position.x;
	float minX = vertices[0].Position.x;
	float maxZ = vertices[0].Position.z;
	float minZ = vertices[0].Position.z;
	for (auto vertex : vertices) {
		auto p = vertex.Position;
		maxY = std::max(maxY, p.y);
		minY = std::min(minY, p.y);
		maxX = std::max(maxX, p.x);
		minX = std::min(minX, p.x);
		maxZ = std::max(maxZ, p.z);
		minZ = std::min(minZ, p.z);
	}
	aabb = AABB(maxY, minY, maxX, minX, maxZ, minZ);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(ShaderProgram& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	int textureUnit = 0;
	for (int i = 0; i < diffuseTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit); // activate proper texture unit before binding
		textureUnit++;
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		shader.setUniform(("material.texture_diffuse" + i), i);
		glBindTexture(GL_TEXTURE_2D, diffuseTextures[i].getID());
	}
	for (int i = 0; i < specularTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit); // activate proper texture unit before binding
		textureUnit++;
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		shader.setUniform(("material.texture_specular" + i), i);
		glBindTexture(GL_TEXTURE_2D, diffuseTextures[i].getID());
	}
	shader.setUniform(("material.color"), color);

	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

const AABB& Mesh::GetAABB()
{
	return aabb;
}
