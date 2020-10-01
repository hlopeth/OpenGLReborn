#pragma once

struct Texture
{
	unsigned char* data;
	unsigned int width;
	unsigned int height;
	Texture() :
		data(nullptr), width(0), height(0) {};
	Texture(unsigned char* _data, unsigned int _width, unsigned int _height) :
		data(_data), width(_width), height(_height) {}
};

extern const Texture nullTexture;