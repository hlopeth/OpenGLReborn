#pragma once
#include "ModelLoader.h"

#ifndef MODEL_LOADER
#define MODEL_LOADER ModelLoaderManager().getModelLoader()
#endif // !MODEL_LOADER

class ModelLoaderManager {
public:
	void initialize();
	void destroy();
	ModelLoader& getModelLoader();
private:
	static ModelLoader* modelLoader;
};