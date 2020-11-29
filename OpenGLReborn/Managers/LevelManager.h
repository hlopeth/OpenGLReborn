#pragma once
#include "Level.h"

#ifndef LEVEL
#define LEVEL LevelManager().getLevel()
#endif // !LEVEL


class LevelManager {
public:
	void initialize();
	void destroy();
	Level& getLevel();
private:
	static Level* level;
};