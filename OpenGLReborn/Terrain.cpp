#include "Terrain.h"

Terrain::Terrain(Texture heightMap, GLTexture texture):
	mesh(generateMesh(heightMap, texture))
{
	shader = ShaderProgram("TexturedVertex.glsl", "TexturedFragment.glsl");
}

void Terrain::draw(RenderData& renderData)
{
	shader.use();
	shader.setUniform("model", getModelMatrix());
	shader.setUniform("mvp", renderData.camera.getViewProjection() * getModelMatrix());
	mesh->Draw(shader);
}

Terrain::~Terrain()
{
	delete mesh;
}

float Terrain::getLowestPoint() const
{
	return lowestPoint;
}

float Terrain::getHightestPoint() const
{
	return hightestPoint;
}

Mesh* Terrain::generateMesh(Texture heightmap, GLTexture texture)
{
	auto width = heightmap.width;
	auto height = heightmap.height;
	vector<Vertex> vertices(width * height);
	vector<unsigned int> indices;

	unsigned int currVertIndex = 0;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Vertex& vertex = vertices[x * width + y];
			float vertexHeight = heightmap.data[(x * width + y) * 2];

			lowestPoint = min(lowestPoint, vertexHeight);
			hightestPoint = max(hightestPoint, vertexHeight);

			vertex.Position = vec3(x, vertexHeight, y);
			vertex.Normal = vec3(0.0, 1.0, 0.0);
			vertex.TexCoords = vec2((50 * (float)x) / width, (50 * (float)y) / height);

			//пропускаем первую строчку и столбец карты высот
			if (y > 0 && x > 0)
			{
				indices.push_back(currVertIndex);
				indices.push_back(currVertIndex - width);
				indices.push_back(currVertIndex - width - 1);

				indices.push_back(currVertIndex);
				indices.push_back(currVertIndex - width - 1);
				indices.push_back(currVertIndex - 1);
			}
			currVertIndex++;
		}
	}

	return new Mesh(
		vertices,
		indices,
		vec3(0.0, 1.0, 0.0),
		{ texture }
	);
}
