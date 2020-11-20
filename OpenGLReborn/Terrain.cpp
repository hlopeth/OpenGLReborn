#include "Terrain.h"
#include "HeightfieldPhysicsBody.h"
#include "TerrainMaterial.h"

Terrain::Terrain(Texture heightMap, shared_ptr<TerrainMaterial> _material): material(_material)
{
	generateMesh(heightMap);
}

void Terrain::draw(RenderData& renderData)
{
	if (shouldUpload) 
	{
		upload();
		shouldUpload = false;
	}
	material->draw(VAO, indices.size(), getModelMatrix(), renderData);
}

float Terrain::getLowestPoint() const
{
	return lowestPoint;
}

float Terrain::getHightestPoint() const
{
	return hightestPoint;
}

void Terrain::generateMesh(Texture heightmap)
{
	auto textureWidth = heightmap.width;
	auto textureHeight = heightmap.height;
	vertices = std::vector<TerrainVertex>(textureWidth * textureHeight);

	unsigned int currVertIndex = 0;

	const float sandLevel = 20;
	const float rockLevel = 100;

	lowestPoint = heightmap.data[0];
	hightestPoint = heightmap.data[0];

	for (int x = 0; x < textureWidth; x++) {
		for (int y = 0; y < textureHeight; y++) {
			TerrainVertex& vertex = vertices[x * textureWidth + y];
			float vertexHeight = heightmap.data[(x * textureWidth + y) ];
			float upHeight = y > 0 ? heightmap.data[(x * textureWidth + y - 1)] : vertexHeight;
			float rightHeight = x < textureWidth - 1 ? heightmap.data[((x + 1) * textureWidth + y)] : vertexHeight;

			//vec3 normal = normalize(vec3(vertexHeight - upHeight, vertexHeight - rightHeight, 1.0));
			vec3 normal = normalize(vec3((rightHeight - vertexHeight), 1.0, (upHeight - vertexHeight)));

			lowestPoint = glm::min(lowestPoint, vertexHeight);
			hightestPoint = glm::max(hightestPoint, vertexHeight);

			float alphaSand = vertexHeight <= sandLevel ? 1.0 : 0.0;
			float alphaGrass = sandLevel <= vertexHeight && vertexHeight <= rockLevel ? 1.0 : 0.0;
			float alphaRock = vertexHeight >= rockLevel ? 1.0 : 0.0;

			vertex.Position = vec3((float)x - textureWidth/2.0, (float)vertexHeight, (float)y - textureHeight/2.0);
			vertex.Normal = normal;
			vertex.UV1 = vec2((50 * (float)x) / textureWidth, (50 * (float)y) / textureHeight);
			vertex.Alphas = vec3(alphaSand, alphaGrass, alphaRock);

			//пропускаем первую строчку и столбец карты высот
			if (y > 0 && x > 0)
			{
				indices.push_back(currVertIndex);
				indices.push_back(currVertIndex - textureWidth);
				indices.push_back(currVertIndex - textureWidth - 1);

				indices.push_back(currVertIndex);
				indices.push_back(currVertIndex - textureWidth - 1);
				indices.push_back(currVertIndex - 1);
			}
			currVertIndex++;
		}
	}

	//центрация по y потому, что bullet так делает
	float d = (hightestPoint - lowestPoint) / 2.0;
	for (int i = 0; i < textureWidth * textureHeight; i++) {
		vertices[i].Position.y -= hightestPoint - d;
	}
	//hightestPoint -= d;
	//lowestPoint -= d;
}

void Terrain::upload()
{
	GLuint VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TerrainVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, UV1));
	// vertex tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, Alphas));

	glBindVertexArray(0);
}
