#include "Water.h"

Water::Water(float width, float height, shared_ptr<WaterMaterial> material) :
	Model(
		make_shared<Mesh>(),
		material
	)
{
	mesh = generateMesh(width, height);
}

void Water::update(double gameTime, double deltaTime)
{
	std::dynamic_pointer_cast<WaterMaterial>(material)->time += 0.008 * deltaTime;
}

shared_ptr<Mesh> Water::generateMesh(float width, float height)
{
	std::vector<Vertex> vertices(width * height);
	std::vector<uint32_t> indices;

	uint32_t currVertIndex = 0;
	for(int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			Vertex& vertex = vertices[x * width + y];
			vertex.Position = glm::vec3(x, 0.0, y);
			vertex.TexCoords = glm::vec2(((float)x) / width, ((float)y) / height);
			vertex.Normal = glm::vec3(0.0, 1.0, 0.0);

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
	return make_shared<Mesh>(vertices, indices);
}
