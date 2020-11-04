#pragma once
#include <string>

class ModelReadExeption
{
public:
	ModelReadExeption(std::string _filename, std::string _message);
	const std::string& getMessage() const;
	const std::string& getFilename() const;
private:
	std::string message;
	std::string filename;
};