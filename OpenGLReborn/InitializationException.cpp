#include "InitializationException.h"

InitializationException::InitializationException(string message)
{
	this->message = message;
}

const string& InitializationException::getMessage() const
{
	return message;
}
