#include "Model.h"

Model::Model(vector<Mesh> meshes)
{
	for(auto mesh: meshes)
	{
		this->meshes.push_back(mesh);
	}
}

void Model::Draw(ShaderProgram& shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) 
	{
		meshes[i].Draw(shader);
	}
}

vector<Mesh>& Model::GetMesh()
{
	return meshes;
}

void Model::loadModel(string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	glm::vec3 color;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		//process vertex positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		//process vertex normals
		if(true)//if (mesh->mNormals != NULL)
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		else
			vertex.Normal = glm::vec3(0.0f);

		//process vertex texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		
		vertices.push_back(vertex);
	}
	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	vector<GLTexture> diffuseTextures;
	vector<GLTexture> ambientTextures;
	vector<GLTexture> emissiveTextures;
	vector<GLTexture> unknownTextures;
	vector<GLTexture> specularTextures;
	// process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex]; 
		aiColor4D diffuse; 
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
			color = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
		loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", diffuseTextures);
		loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_ambient", ambientTextures);
		loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive", emissiveTextures);
		loadMaterialTextures(material, aiTextureType_UNKNOWN, "texture_unknown", unknownTextures);
		loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", specularTextures);
	}

	return Mesh(vertices, indices, color, diffuseTextures, ambientTextures, emissiveTextures, specularTextures);
}

void Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, vector<GLTexture> &outTextures)
{
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		outTextures.emplace_back(str.C_Str(), directory, GL_RGBA);
	}
}
