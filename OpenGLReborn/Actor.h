#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "map"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Actor
{
public:
	/*  Functions   */
	Actor(const char *path)
	{
		loadModel(path);
	}
	void Draw(ShaderProgram shader);
private:
	/*  Model Data  */
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};


unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);