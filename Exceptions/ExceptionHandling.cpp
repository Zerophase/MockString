//
// Created by zerophase on 5/30/21.
//

#include "ExceptionHandling.h"
#if !USE_PRECOMPILED
	#include <iostream>
#endif

DialogueError::DialogueError(vector<FastString> errors) :
		runtime_error("")
{
	this->errors = move(errors);
}

void DialogueError::Output()
{
	for(const auto &e : errors)
		std::cout << e.cstring << std::endl;
}
