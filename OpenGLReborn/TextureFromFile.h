#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <libpng/png.h>
#include <iostream>

//#pragma comment(lib, "libpng16_staticd.lib")

using std::string;

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);