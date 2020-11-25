#include "ModelReadException.h"

ModelReadException::ModelReadException(
	std::string _filename,
	std::string _message) :
	filename(_filename),
	message(_message)
{
}

const std::string& ModelReadException::getMessage() const
{
	return message;
}

const std::string& ModelReadException::getFilename() const
{
	return filename;
}
