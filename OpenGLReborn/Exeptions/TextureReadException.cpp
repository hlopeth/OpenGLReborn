#include "TextureReadException.h"

TextureReadException::TextureReadException(
	std::string _filename,
	std::string _message): 
	filename(_filename),
	message(_message)
{
}

const std::string& TextureReadException::getMessage() const
{
	return message;
}

const std::string& TextureReadException::getFilename() const
{
	return filename;
}
