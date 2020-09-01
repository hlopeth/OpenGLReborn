#include "InitialisationExeption.h"

InitialisationExeption::InitialisationExeption(string message)
{
	this->message = message;
}

const string& InitialisationExeption::getMessage() const
{
	return message;
}
