#include "Terrain.h"
#include <bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.h>

Terrain::Terrain(Texture heightMap, GLTexture texture):
	mesh(generateMesh(heightMap, texture))
{
	shader = ShaderProgram("terrainVertex.glsl", "terrainFragment.glsl");
}

void Terrain::draw(RenderData& renderData)
{
	shader.use();
	shader.setUniform("model", getModelMatrix());
	shader.setUniform("mvp", renderData.camera.getViewProjection() * getModelMatrix());

	shader.setUniform("cameraPos", renderData.camera.pos);
	PointLight* pointLight = nullptr;
	int pointLightsSize = renderData.pointLights.size();
	shader.setUniform("n_pointLights", pointLightsSize);
	for (unsigned int i = 0; i < pointLightsSize; i++)
	{
		pointLight = renderData.pointLights[i];
		char ch_i = '0' + i;
		shader.setUniform(string("pointLights[") + ch_i + "].position", pointLight->position);
		shader.setUniform(string("pointLights[") + ch_i + "].ambient", pointLight->ambient);
		shader.setUniform(string("pointLights[") + ch_i + "].diffuse", pointLight->diffuse);
		shader.setUniform(string("pointLights[") + ch_i + "].specular", pointLight->specular);
		shader.setUniform(string("pointLights[") + ch_i + "].constant", pointLight->constant);
		shader.setUniform(string("pointLights[") + ch_i + "].linear", pointLight->linear);
		shader.setUniform(string("pointLights[") + ch_i + "].quadratic", pointLight->quadratic);
		shader.setUniform(string("pointLights[") + ch_i + "].farPlane", pointLight->farPlane);
	}

	shader.setUniform("directinalLight.direction", renderData.dirextinalLight->direction);
	shader.setUniform("directinalLight.color", renderData.dirextinalLight->color);

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

Mesh& Terrain::getMesh()
{
	return *mesh;
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

			float upHeight = y > 0 ? heightmap.data[(x * width + y - 1) * 2] : vertexHeight;
			float rightHeight = x < width - 1 ? heightmap.data[((x + 1) * width + y) * 2] : vertexHeight;

			vec3 normal = normalize(vec3(vertexHeight - upHeight, vertexHeight - rightHeight, 1.0));

			lowestPoint = min(lowestPoint, vertexHeight);
			hightestPoint = max(hightestPoint, vertexHeight);

			vertex.Position = vec3(x, vertexHeight, y);
			vertex.Normal = normal;
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
