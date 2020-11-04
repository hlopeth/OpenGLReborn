#include "ModelReadExeprion.h"

ModelReadExeption::ModelReadExeption(
	std::string _filename,
	std::string _message) :
	filename(_filename),
	message(_message)
{
}

const std::string& ModelReadExeption::getMessage() const
{
	return message;
}

const std::string& ModelReadExeption::getFilename() const
{
	return filename;
}
