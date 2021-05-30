//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_EXCEPTIONHANDLING_H
#define MOCKSTRING_EXCEPTIONHANDLING_H

#include <stdexcept>
#include "Strings/FastString.h"
#include <vector>

using namespace StringManipulation;
using std::runtime_error;
using std::vector;

class ReadOnlyError : public runtime_error
{
	using runtime_error::runtime_error;
};

class XmlFileError : public runtime_error
{
	using runtime_error::runtime_error;
};

class DialogueError : public runtime_error
{
public:
	explicit DialogueError(vector<FastString> errors);
	void Output();

private:
	vector<FastString> errors;
};

#endif //MOCKSTRING_EXCEPTIONHANDLING_H
