//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_STRINGMANIPULATION_H
#define MOCKSTRING_STRINGMANIPULATION_H

//#include "GeneralMacros/FORCE_INLINE.h"
//#include "BinaryTree/Node.h"

#include <cstddef>

namespace StringManipulation
{
	struct FastString;
	
	FastString StripComments(FastString &str);
	FastString stripWhite(FastString &str);
	size_t FindFirstOf(FastString &str, const char * characters);
	size_t FindFirstNotOf(FastString &str, const char *characters);
	size_t FindLastOf(FastString &str, char characters);
	FastString Substring(const FastString &str, size_t str_start, size_t new_line);
	
	size_t FindFirstOf(FastString &str, size_t pos, const char *characters);
	
	static const char *delimiter = "==<>>=<=!=";
};


#endif //MOCKSTRING_STRINGMANIPULATION_H
