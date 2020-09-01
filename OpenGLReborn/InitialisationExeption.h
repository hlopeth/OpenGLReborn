#pragma once
#include <string>

using std::string;

class InitialisationExeption
{
public:
	InitialisationExeption(string message);
	const string& getMessage() const;
private:
	string message;
};