#include "Mesh.h"
#include <algorithm>

Mesh::Mesh()
{
	VAO = -1;
	VBO = -1;
	EBO = -1;
}

Mesh::Mesh(
	vector<Vertex> vertices,
	vector<unsigned int> indices
) {
	this->vertices = vertices;
	this->indices = indices;
	setupMesh();
}

GLuint Mesh::getVAO() const
{
	return VAO;
}

GLuint Mesh::getVBO() const
{
	return VBO;
}

GLuint Mesh::getEBO() const
{
	return EBO;
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
	// vertex tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangents));
	// vertex bitangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangents));

	glBindVertexArray(0);
}

const AABB& Mesh::getAABB() const
{
	return aabb;
}
