//
// Created by zerophase on 5/30/21.
//

#ifndef MOCKSTRING_CSTRING_H
#define MOCKSTRING_CSTRING_H
#pragma once

#include "../Catch2/catch.hpp"
#include "../Catch2/trompeloeil.hpp"

inline auto cstring(const char *string)
{
	return trompeloeil::make_matcher<const char*>(
			[](const char *value, const char *alternative)
			{
				return std::strcmp(value, alternative) == 0;
			},
			
			[](std::ostream &os, const char *alternative)
			{
				os << " error cstring does not match.";
			},
			string
	);
	
}

#endif //MOCKSTRING_CSTRING_H
