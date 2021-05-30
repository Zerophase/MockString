//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_MOCKSTRINGMANIPULATION_H
#define MOCKSTRING_MOCKSTRINGMANIPULATION_H
#pragma once

#include "../Catch2/catch.hpp"
#include "../Catch2/trompeloeil.hpp"
#include "Strings/StringManipulation.h"
#include "Strings/FastString.h"

using namespace StringManipulation;

class MockStringManipulation
{
public:
	MAKE_MOCK1(stripWhite, FastString(FastString&));
	MAKE_MOCK2(FindFirstOf, size_t(FastString&, const char*));
	MAKE_MOCK2(FindFirstNotOf, size_t(FastString&, const char*));
	MAKE_MOCK2(FindLastOf, size_t(FastString&, char));
	MAKE_MOCK3(Substring, FastString(const FastString&, size_t, size_t));
	
	MAKE_MOCK1(StripComments, FastString(FastString&));
	MAKE_MOCK1(StripComparison, char*(char*));
	MAKE_MOCK1(StripComparison, FastString(const FastString&));
	
	MAKE_MOCK1(ConvertDotToDereference, char*(char*));
	MAKE_MOCK1(ConvertDotToDereference, void(FastString&));
	MAKE_MOCK1(ConvertToMethod, void(FastString&));
	
	MAKE_MOCK1(GrabComparison, FastString(const FastString&));
	MAKE_MOCK1(GrabProperty, FastString(const FastString&));
	
	MAKE_MOCK2(StrcatCopy, const char*(const char*, const char*));
	MAKE_MOCK2(strstr, char*(const FastString&, const char*));
	
	MAKE_MOCK3(ReplaceAll, const char*(const char*, char, char));
	MAKE_MOCK2(ReplaceAllSubstring, char*(const FastString&, const char*));
	MAKE_MOCK3(ReplaceAllSubstringWith, char*(const FastString &, const char*, const char*));
	
	MAKE_MOCK1(LowerCaseFirstLetter, FastString(FastString &));
	MAKE_MOCK1(LowerCaseAll, FastString(FastString&));
	MAKE_MOCK2(LowerCaseAt, FastString(FastString&, int));
	MAKE_MOCK2(LowerCaseAt, void(char*, int));
	MAKE_MOCK1(UpperCase, void(FastString&));
	
	MAKE_MOCK1(RemovePunctuation, void(FastString&));
	
	MAKE_MOCK1(CopyStringToChar, char*(const FastString&));
	
	MAKE_MOCK2(findsubstr, size_t(const FastString&, const FastString&));
	
	MAKE_MOCK3(FindFirstOf, size_t(FastString&, size_t, const char*));
	
	MAKE_MOCK1(ParseDigit, char(char*));
};

extern MockStringManipulation mockStringManipulation;
#endif //MOCKSTRING_MOCKSTRINGMANIPULATION_H
