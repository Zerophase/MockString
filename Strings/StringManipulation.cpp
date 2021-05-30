//
// Created by zerophase on 5/30/21.
//

#include "StringManipulation.h"
#include "BitTwiddling/BitHacks.h"
#include <cstring>
#include <cctype>
#include <stdexcept>
#include "GeneralMacros/NPOS.h"
#include "FastString.h"

namespace StringManipulation
{
	using namespace BitTwiddle;
	using std::strstr;
	
	FastString StripComments(FastString &str)
	{
		FastString temp = stripWhite(str);
		size_t check = FindFirstOf(temp, "//");
		if (check != NPOS)
		{
			unsigned long start = FindFirstNotOf(temp, "\n");
			unsigned long end = FindLastOf(temp, '\n'); //+ 1 - start;
			return Substring(temp, start, end);
		}
		try
		{
			size_t end = FindLastOf(temp, '\n');
			if (end == NPOS)
				return temp;
			return Substring(temp, 0, end + 1);
		}
		catch (...)
		{
			throw std::runtime_error("Invalid instruction or condition");
		}
	}
	
	FastString stripWhite(FastString &str)
	{
		char *end;
		char *curString = str.cstring;
		while (isspace((unsigned char) *curString))
			curString++;
		
		if (*str.cstring == 0) // TODO see if can be removed. Never returns true
			return str;
		
		str.eraseFromStart(str.cstring - curString);
		end = str.GetEndofString();
		while (end > str.cstring && isspace((unsigned char) *end))
			end--;
		*(end + 1) = 0;
		return str;
	}
	
	size_t FindFirstOf(FastString &str, const char *characters)
	{
		char *firstOf = strstr(str.cstring, characters);
		if (firstOf == nullptr)
			return -1;
		return firstOf - str.cstring;
	}
	
	size_t FindFirstOf(FastString &str, size_t pos, const char *characters)
	{
		char *firstOf = strstr(str.cstring + pos, characters);
		return firstOf - str.cstring;
	}
	
	size_t FindFirstNotOf(FastString &str, const char *characters)
	{
		size_t size = FindFirstOf(str, characters) + 1;
		size_t lenc = strlen(characters);
		while (strncmp(str.cstring + size, characters, lenc) == 0)
			size = FindFirstOf(str, size, characters) + 1;
		return size;
	}
	
	size_t FindLastOf(FastString &str, const char character)
	{
		char *strEnd = strrchr(str.cstring, character); // FIXME doesn't work for multiple substrings
		if (strEnd == nullptr)
			return -1;
		return strEnd - str.cstring;
	}
	
	// TODO rename. str_start is where the string starts. new_line is the position of
	// the \n prior to the start
	FastString Substring(const FastString &str, size_t str_start, size_t new_line)
	{
		char *strStart = str.cstring + str_start;
		char *strEnd = strStart + (new_line - str_start);
		char save = *strEnd;
		*strEnd = 0;
		FastString temp(strStart);
		*strEnd = save;
		return temp;
	}
	
	char *strstr(const FastString& str1, const char *str2)
	{
		return strstr(str1.cstring, str2);
	}
}
