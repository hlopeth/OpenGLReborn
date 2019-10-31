#pragma once
#include <string>

using std::string;

class InitialisationExeption
{
public:
	InitialisationExeption(string message);
	string getMessage();
private:
	string message;
};