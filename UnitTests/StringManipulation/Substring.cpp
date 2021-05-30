//
// Created by zerophase on 5/30/21.
//

#include "UnitTests/Catch2/catch.hpp"
#include "Strings/FastString.h"
#include "Strings/StringManipulation.h"

using namespace StringManipulation;
using Catch::Matchers::Equals;

TEST_CASE("Substring")
{
SECTION("Remove new line at start")
{
FastString test("\ntest");

FastString result = Substring(test, 0, 5);

CHECK_THAT(result.cstring, Equals("test"));
}
}
