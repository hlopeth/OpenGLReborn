#include "MeshPrimitives.h"

vector<Vertex> boxVertices{
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
		  
	Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f)},
		  
	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
		  
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
		  
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
		  
	Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f)}
};

const vector<unsigned int> boxIndices {
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36
};

const vector<Vertex> planeVertices{
	Vertex{glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  0.0f, -1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3( 1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f,  0.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f,  0.0f, -1.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f)}
};

const vector<unsigned int> planeIndices{
	0, 1, 2, 3, 4, 5
};

Texture defaultTexture;
//const unsigned char textureData[] = {
//	255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255,
//	0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,
//	255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255,
//	0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,
//	255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255,
//	0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,
//	255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255,
//	0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255,0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255
//};

Mesh RenderingPrimitives::Box(vector<Texture> textures, glm::vec3 color)
{
	return Mesh(boxVertices, boxIndices, textures, color);
}

Mesh RenderingPrimitives::Plane(vector<Texture> textures, glm::vec3 color)
{
	return Mesh(planeVertices, planeIndices, textures, color);
}

Texture RenderingPrimitives::DefaultTexture()
{
	if (defaultTexture.id == -1)
	{
		int width = 256;
		int height = 256;
		int cellSize = 8;
		unsigned char* textureData = new unsigned char[width * height * 4];
		int t = cellSize * 2;
		for(int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
			{
				int kx = (x / cellSize) % 2;
				int ky = (y / cellSize) % 2;
				int i = (x * width + y) * 4;
				if (kx == ky)
				{
					textureData[i] = 0;
					textureData[i + 1] = 0;
					textureData[i + 2] = 0;
					textureData[i + 3] = 255;
				}
				else
				{
					textureData[i] = 255;
					textureData[i + 1] = 255;
					textureData[i + 2] = 255;
					textureData[i + 3] = 255;
				}
			}


		glGenTextures(1, &defaultTexture.id);

		glBindTexture(GL_TEXTURE_2D, defaultTexture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		defaultTexture.type = "texture_diffuse";
	}
	return defaultTexture;
}
