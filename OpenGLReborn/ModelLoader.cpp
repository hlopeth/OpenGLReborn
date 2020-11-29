#include "ModelLoader.h"
#include "Exeptions/ModelReadException.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "TextureFromFile.h"

using Assimp::Importer;

string directory;

void processNode(aiNode* node, const aiScene& scene, ModelLoader& modelLoader, shared_ptr<ModelData> outModelData);
void processMesh(const aiMesh& mesh, const aiScene& scene, Mesh& outMesh);
void processTextures(
	const aiMaterial& material,
	const aiScene& scene,
	ModelLoader& modelLoader,
	vector<shared_ptr<Texture>>& outTextures
);
glm::vec3 processColor(const aiMaterial& material, const aiScene& scene);
TextureType aiTypeToTextureType(aiTextureType aiType);

shared_ptr<ModelData> ModelLoader::loadModel(const string& path)
{
	auto cashedModel = loadedModels.find(path);
	if (cashedModel != loadedModels.end())
	{
		return cashedModel->second;
	}

	Importer importer;
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
	);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw new ModelReadException(path, importer.GetErrorString());
		return make_shared<ModelData>();
	}
	auto modelData = make_shared<ModelData>();
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, *scene, *this, modelData);
	return modelData;
}


void processNode(aiNode* node, const aiScene& scene, ModelLoader& modelLoader, shared_ptr<ModelData> outModelData)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		ModelNodeData modelNodeData;
		const aiMesh *mesh = scene.mMeshes[node->mMeshes[i]];
		processMesh(*mesh, scene, modelNodeData.mesh);
		if (mesh->mMaterialIndex >= 0) {
			const aiMaterial *material = scene.mMaterials[mesh->mMaterialIndex];
			processTextures(*material, scene, modelLoader, modelNodeData.textures);
			modelNodeData.color = processColor(*material, scene);
		}
		outModelData->push_back(modelNodeData);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, modelLoader, outModelData);
	}
}

void processMesh(const aiMesh& mesh, const aiScene& scene, Mesh& outMesh)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	glm::vec3 color;

	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 tmpVector;

		//process vertex positions
		tmpVector.x = mesh.mVertices[i].x;
		tmpVector.y = mesh.mVertices[i].y;
		tmpVector.z = mesh.mVertices[i].z;
		vertex.Position = tmpVector;

		//process vertex normals
		if (true)//if (mesh->mNormals != NULL)
		{
			tmpVector.x = mesh.mNormals[i].x;
			tmpVector.y = mesh.mNormals[i].y;
			tmpVector.z = mesh.mNormals[i].z;
			vertex.Normal = tmpVector;
		}
		else
			vertex.Normal = glm::vec3(0.0f);

		tmpVector.x = mesh.mTangents[i].x;
		tmpVector.y = mesh.mTangents[i].y;
		tmpVector.z = mesh.mTangents[i].z;
		vertex.Tangents = tmpVector;

		tmpVector.x = mesh.mBitangents[i].x;
		tmpVector.y = mesh.mBitangents[i].y;
		tmpVector.z = mesh.mBitangents[i].z;
		vertex.Bitangents = tmpVector;



		//process vertex texture coordinates
		if (mesh.mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh.mTextureCoords[0][i].x;
			vec.y = mesh.mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// process indices
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		aiFace face = mesh.mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	outMesh = Mesh(vertices, indices);
}


void processTextures(
	const aiMaterial& material, 
	const aiScene& scene, 
	ModelLoader& modelLoader, 
	vector<shared_ptr<Texture>>& outTextures
)
{
	aiString aiPath;
	string path;
	aiTextureType textureTypes[] = { 
		aiTextureType_DIFFUSE, 
		aiTextureType_EMISSIVE, 
		aiTextureType_UNKNOWN,
		aiTextureType_SPECULAR,
		aiTextureType_HEIGHT
	};
	for (aiTextureType aiType : textureTypes) 
	{
		for (unsigned int i = 0; i < material.GetTextureCount(aiType); i++)
		{
			material.GetTexture(aiType, i, &aiPath);
			path = string(aiPath.C_Str());
			TextureType textureType = aiTypeToTextureType(aiType);
			auto texture = modelLoader.loadTexture(path, directory, textureType);
			outTextures.push_back(texture);
		}
	}
}

glm::vec3 processColor(const aiMaterial& material, const aiScene& scene)
{
	glm::vec3 color = glm::vec3(0.0);
	aiColor4D diffuse;
	if (AI_SUCCESS == aiGetMaterialColor(&material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color = glm::vec3(diffuse.r, diffuse.g, diffuse.b);

	return color;
}

TextureType aiTypeToTextureType(aiTextureType aiType) 
{
	TextureType textureType = TextureType::UNKNOWN;
	switch (aiType)
	{
	case aiTextureType_DIFFUSE:
		textureType = TextureType::DIFFUSE;
		break;
	case aiTextureType_AMBIENT:
		textureType = TextureType::AMBIENT;
		break;
	case aiTextureType_EMISSIVE:
		textureType = TextureType::EMISSIVE;
		break;
	case aiTextureType_SPECULAR:
		textureType = TextureType::SPECULAR;
		break;
	case aiTextureType_HEIGHT:
		textureType = TextureType::NORMAL;
		break;
	default:
		textureType = TextureType::UNKNOWN;
		break;
	}
	return textureType;
}

shared_ptr<Texture> ModelLoader::loadTexture(const string& path, const string& directory, TextureType type)
{
	auto cashedTexture = loadedTextures.find(path);
	if (cashedTexture != loadedTextures.end()) {
		return cashedTexture->second;
	}

	shared_ptr<Texture> texture = make_shared<Texture>(TextureFromFile(path.c_str(), directory));
	texture->type = type;
	loadedTextures[directory + '/' + path] = texture;
	return texture;
}