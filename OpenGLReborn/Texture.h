#pragma once

enum TextureType {
	UNKNOWN,
	DIFFUSE,
	AMBIENT,
	EMISSIVE,
	SPECULAR,
	NORMAL
};

struct Texture
{
	unsigned char* data;
	unsigned int width;
	unsigned int height;
	TextureType type;
	Texture() :
		data(nullptr), width(0), height(0), type(UNKNOWN) {};
	Texture(unsigned char* _data, unsigned int _width, unsigned int _height, TextureType _type = TextureType::UNKNOWN) :
		data(_data), width(_width), height(_height), type(_type) {}
};

extern const Texture nullTexture;