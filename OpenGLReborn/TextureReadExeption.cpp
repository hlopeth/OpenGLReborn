#include "TextureReadExeption.h"

TextureReadExeption::TextureReadExeption(
	std::string _filename,
	std::string _message): 
	filename(_filename),
	message(_message)
{
}

const std::string& TextureReadExeption::getMessage() const
{
	return message;
}

const std::string& TextureReadExeption::getFilename() const
{
	return filename;
}
