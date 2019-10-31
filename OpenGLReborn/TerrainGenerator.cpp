#include "TerrainGenerator.h"
#include <vector>
#include "PerlinNoise.h"

auto perlin = PerlinNoise();

double noise(double x, double y, double f1, double f2, double f3, double s1, double s2, double s3)
{
	return s1 * perlin.noise(f1 * x, f1 * y, 0) + s2 * perlin.noise(f2 * x, f2 * y, 10) + s3 * perlin.noise(f3 * x, f3 * y, 20);
}

Model TerrainGenerator::generate(int width, int height, int n)
{
	using  std::vector;
	auto vertices = vector<Vertex>(n * n);
	auto indices = vector<unsigned int>(6 * (n - 1) * (n - 1));
	auto textures = vector<Texture>(0);
	auto color = vec3(0.0);

	double x = 0.0;
	double z = 0.0;

	int lastIndex = 0;

	double freq = 0.03;
	
	for (int i = 0; i < n; i++) 
	{
		z = 0.0;
		for (int j = 0; j < n; j++)
		{
			Vertex vertex;
			double y = noise(x, z, 0.025, 0.08, 0.03, 55, 15, 0);
			vertex.Position = vec3(x, y, z);
			vertex.Normal = vec3(0.0, 0.0, 0.0);
			vertex.TexCoords = vec2(0.0, 0.0);
			int vertexIndex = i * n + j;
			vertices[vertexIndex] = vertex;

			if (i > 0 && j > 0) 
			{
				vec3 v1 = vertices[vertexIndex].Position - vertices[vertexIndex - 1].Position;
				vec3 v2 = vertices[vertexIndex].Position - vertices[vertexIndex - n - 1].Position;
				vec3 normal = cross(v1, v2);
				if (normal.y < 0)
					normal = cross(-v1, v2);
				vertices[vertexIndex].Normal = normalize(vertices[vertexIndex].Normal + normal);
				vertices[vertexIndex - 1].Normal = normalize(vertices[vertexIndex - 1].Normal + normal);
				vertices[vertexIndex - 1 - n].Normal = normalize(vertices[vertexIndex - 1 - n].Normal + normal);

				indices[lastIndex++] = vertexIndex;
				indices[lastIndex++] = vertexIndex - 1;
				indices[lastIndex++] = vertexIndex - 1 - n;

				v1 = vertices[vertexIndex].Position - vertices[vertexIndex - n].Position;
				v2 = vertices[vertexIndex].Position - vertices[vertexIndex - n - 1].Position;
				normal = cross(v1, v2);
				if (normal.y < 0)
					normal = cross(-v1, v2);
				vertices[vertexIndex].Normal = normalize(vertices[vertexIndex].Normal + normal);
				vertices[vertexIndex - 1].Normal =normalize(vertices[vertexIndex - 1].Normal + normal);
				vertices[vertexIndex - 1 - n].Normal = normalize(vertices[vertexIndex - 1 - n].Normal + normal);

				indices[lastIndex++] = vertexIndex;
				indices[lastIndex++] = vertexIndex - 1 - n;
				indices[lastIndex++] = vertexIndex - n;
			}
			z += (double)height / n;
		}
		x += (double)width / n;
	}

	auto meshes = vector<Mesh>{ Mesh(vertices, indices, textures, color) };
	return Model(meshes);
}
