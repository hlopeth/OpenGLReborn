#include "InitialisationExeption.h"

InitialisationExeption::InitialisationExeption(string message)
{
	this->message = message;
}

string InitialisationExeption::getMessage()
{
	return message;
}
