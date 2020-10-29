#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "TextureFromFile.h"


class Model
{
public:
	/*  Functions   */
	Model() {}
	Model(vector<Mesh> meshes);
	Model(const char *path)
	{
		loadModel(path);
	}
	void Draw(ShaderProgram& shader);
	vector<Mesh>& GetMesh();
private:
	/*  Model Data  */
	vector<Mesh> meshes;
	vector<GLTexture> textures_loaded;
	string directory;
	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	void loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, vector<GLTexture>& outTextures, int format);
};

