#pragma once
#include <string>

class TextureReadExeption
{
public:
	TextureReadExeption(std::string _filename, std::string _message);
	const std::string& getMessage() const;
	const std::string& getFilename() const;
private:
	std::string message;
	std::string filename;
};