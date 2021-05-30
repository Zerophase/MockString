//
// Created by zerophase on 5/30/21.
//

#include "Strings/StringManipulation.h"
#include "Strings/FastString.h"
#include "MockStringManipulation.h"

namespace StringManipulation
{
	FastString stripWhite(FastString& str)
	{
		return mockStringManipulation.stripWhite(str);
	}
	
	size_t FindFirstOf(FastString &str, const char *tar)
	{
		return mockStringManipulation.FindFirstOf(str, tar);
	}
	
	size_t FindFirstNotOf(FastString &str, const char *tar)
	{
		return mockStringManipulation.FindFirstNotOf(str, tar);
	}
	
	size_t FindLastOf(FastString &str, const char tar)
	{
		return mockStringManipulation.FindLastOf(str, tar);
	}
	
	FastString Substring(const FastString &str, size_t pos, size_t end)
	{
		return mockStringManipulation.Substring(str, pos, end);
	}
}
