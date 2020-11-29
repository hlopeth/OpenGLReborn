#include "ModelLoaderManager.h"

ModelLoader* ModelLoaderManager::modelLoader = nullptr;

void ModelLoaderManager::initialize()
{
	modelLoader = new ModelLoader();
}

void ModelLoaderManager::destroy()
{
	delete modelLoader;
	modelLoader = nullptr;
}

ModelLoader& ModelLoaderManager::getModelLoader()
{
	if (modelLoader == nullptr)
	{
		modelLoader = new ModelLoader();
	}
	return *modelLoader;
}


