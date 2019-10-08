#include "TerrainGenerator.h"
#include <vector>
#include "PerlinNoise.h"

auto perlin = PerlinNoise();

double noise(double x, double y, double f1, double f2, double f3, double s1, double s2, double s3)
{
	return s1 * perlin.noise(f1 * x, f1 * y, 0) + s2 * perlin.noise(f2 * x, f2 * y, 0) + s3 * perlin.noise(f3 * x, f3 * y, 0);
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
			double y = noise(x, z, 0.08, 0.5, 2, 20, 2, 1);
			vertex.Position = vec3(x, y, z);
			vertex.Normal = vec3(0.0, 1.0, 0.0);
			vertex.TexCoords = vec2(0.0, 0.0);
			int vertexIndex = i * n + j;
			vertices[vertexIndex] = vertex;

			if (i > 0 && j > 0) 
			{
				indices[lastIndex++] = vertexIndex;
				indices[lastIndex++] = vertexIndex - 1;
				indices[lastIndex++] = vertexIndex - 1 - n;

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
