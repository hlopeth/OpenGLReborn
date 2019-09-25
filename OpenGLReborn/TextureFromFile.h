#pragma once
#include <string>
#include <iostream>
#include <libpng/png.h>
#include <glad/glad.h>

using std::string;

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);