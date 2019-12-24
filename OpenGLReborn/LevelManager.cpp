#pragma once
#include "LevelManager.h"

Level* LevelManager::level = nullptr;

void LevelManager::initialize()
{
	level = new Level();
}

void LevelManager::destroy()
{
	delete level;
	level = nullptr;
}

Level& LevelManager::getLevel()
{
	return *level;
}
