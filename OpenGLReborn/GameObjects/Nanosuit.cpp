#include "Nanosuit.h"
#include "Material/NanosuitMaterial.h"
#include "Managers/ModelLoaderManager.h"
#include "GLTexture.h"

#define PATH_TO_MODEL "assets/nanosuit/nanosuit.obj"

std::vector<Model> loadModels()
{
	shared_ptr<ModelData> modelData = MODEL_LOADER.loadModel(PATH_TO_MODEL);
	std::vector<Model> models;
	for (int i = 0; i < modelData->size(); i++)
	{
		auto node = (*modelData)[i];

		GLTexture diffuseGLTexture, specularGLTexture, normalGLTexture;
		bool useSpecular = false;

		for (int j = 0; j < node.textures.size(); j++)
		{
			switch (node.textures[j]->type)
			{
			case TextureType::DIFFUSE: 
			{
				Texture diffuseTexture = *node.textures[j];
				diffuseGLTexture = GLTexture(diffuseTexture, GL_RGBA);
				break;
			}
			case TextureType::SPECULAR:
			{
				Texture specularTexture = *node.textures[j];
				specularGLTexture = GLTexture(specularTexture, GL_RGBA);
				useSpecular = true;
				break;
			}
			case TextureType::NORMAL:
			{
				Texture normalTexture = *node.textures[j];
				normalGLTexture = GLTexture(normalTexture, GL_RGB);
				break;
			}
			default:
				break;
			}
		}

		NanosuitMaterial material(
			diffuseGLTexture,
			specularGLTexture,
			normalGLTexture,
			node.color,
			useSpecular
		);

		models.push_back(
			Model(
				make_shared<Mesh>(node.mesh.vertices, node.mesh.indices),
				make_shared<NanosuitMaterial>(material)
			)
		);
	}

	return models;
}

Nanosuit::Nanosuit()
{
	models = loadModels();
}

const std::vector<Model>& Nanosuit::getModel() const
{
	return models;
}

void Nanosuit::draw(RenderData& rd) const
{
	for (int i = 0; i < models.size(); i++)
	{
		models[i].draw(rd);
	}
}