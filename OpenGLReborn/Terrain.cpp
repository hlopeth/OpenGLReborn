#include "Terrain.h"
#include "HeightfieldPhysicsBody.h"
#include "TerrainMaterial.h"

Terrain::Terrain(Texture heightMap, GLTexture texture):
	Model(
		make_shared<Mesh>(generateMesh(heightMap)),
		make_shared<TerrainMaterial>(texture)
	)
{
	shader = ShaderProgram("terrainVertex.glsl", "terrainFragment.glsl");
}

Terrain::~Terrain()
{
	delete mesh;
}

Mesh& Terrain::getMesh()
{
	return *mesh;
}

Mesh Terrain::generateMesh(Texture heightmap)
{
	auto textureWidth = heightmap.width;
	auto textureHeight = heightmap.height;
	vector<Vertex> vertices(textureWidth * textureHeight);
	vector<unsigned int> indices;

	unsigned int currVertIndex = 0;
	

	float lowestPoint = heightmap.data[0];
	float hightestPoint = heightmap.data[0];

	for (int x = 0; x < textureWidth; x++) {
		for (int y = 0; y < textureHeight; y++) {
			Vertex& vertex = vertices[x * textureWidth + y];
			float vertexHeight = heightmap.data[(x * textureWidth + y) * 2];
			float upHeight = y > 0 ? heightmap.data[(x * textureWidth + y - 1) * 2] : vertexHeight;
			float rightHeight = x < textureWidth - 1 ? heightmap.data[((x + 1) * textureWidth + y) * 2] : vertexHeight;

			vec3 normal = normalize(vec3(vertexHeight - upHeight, vertexHeight - rightHeight, 1.0));

			lowestPoint = min(lowestPoint, vertexHeight);
			hightestPoint = max(hightestPoint, vertexHeight);

			vertex.Position = vec3((float)x - textureWidth/2.0, (float)vertexHeight, (float)y - textureHeight/2.0);
			vertex.Normal = normal;
			vertex.TexCoords = vec2((50 * (float)x) / textureWidth, (50 * (float)y) / textureHeight);

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

	return Mesh(
		vertices,
		indices
	);
}
