#pragma once
#include <string>

using std::string;

class InitializationException
{
public:
	InitializationException(string message);
	const string& getMessage() const;
private:
	string message;
};