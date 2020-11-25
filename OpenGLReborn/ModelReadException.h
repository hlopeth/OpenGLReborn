#pragma once
#include <string>

class ModelReadException
{
public:
	ModelReadException(std::string _filename, std::string _message);
	const std::string& getMessage() const;
	const std::string& getFilename() const;
private:
	std::string message;
	std::string filename;
};