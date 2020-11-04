#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "Mesh.h"
#include "Texture.h"

struct ModelNodeData {
	Mesh mesh;
	std::vector<shared_ptr<Texture>> textures;
	glm::vec3 color;
};

typedef std::vector<ModelNodeData> ModelData;

class ModelLoader {
public:
	shared_ptr<ModelData> loadModel(const string& path);
	shared_ptr<Texture> loadTexture(const string& path, const string& directory, TextureType type);
private:
	std::map<std::string, shared_ptr<ModelData>> loadedModels;
	std::map<std::string, shared_ptr<Texture>> loadedTextures;
};