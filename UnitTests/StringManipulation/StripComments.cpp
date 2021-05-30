//
// Created by zerophase on 5/30/21.
//

#include "UnitTests/Catch2/catch.hpp"
#include "UnitTests/Catch2/trompeloeil.hpp"
#include "UnitTests/Matchers/cstring.h"
#include "UnitTests/Mocks/MockStringManipulation.h"
#include "Strings/StringManipulation.h"
#include "Strings/FastString.h"
#include "GeneralMacros/NPOS.h"

using namespace StringManipulation;
using Catch::Matchers::Equals;

MockStringManipulation mockStringManipulation;

TEST_CASE("Strip Comments", "[StringManipulationTests]")
{
SECTION("Comments")
{
FastString test(" //blah\ntest");
FastString whiteStripped("//blah\ntest");
FastString output("test");
REQUIRE_CALL(mockStringManipulation, stripWhite(test))
.RETURN(whiteStripped);
REQUIRE_CALL(mockStringManipulation, FindFirstOf(whiteStripped, cstring("//")))
.RETURN(0);
REQUIRE_CALL(mockStringManipulation, FindFirstNotOf(whiteStripped, cstring("\n")))
.RETURN(7);
REQUIRE_CALL(mockStringManipulation, FindLastOf(whiteStripped, '\n'))
.RETURN(6);
REQUIRE_CALL(mockStringManipulation, Substring(whiteStripped, 7, 6))
.RETURN(output);

FastString result = StripComments(test);

CHECK_THAT(result.cstring, Equals("test"));
}

SECTION("No comments")
{
FastString test("test");

SECTION("no new line left")
{
REQUIRE_CALL(mockStringManipulation, stripWhite(test))
.RETURN(test);
REQUIRE_CALL(mockStringManipulation, FindFirstOf(test, cstring("//")))
.RETURN(NPOS);
REQUIRE_CALL(mockStringManipulation, FindLastOf(test, '\n'))
.RETURN(NPOS);

FastString result = StripComments(test);
CHECK_THAT(result.cstring, Equals("test"));
}

SECTION("new line at the start")
{
FastString curTest = FastString("\n") + test;
REQUIRE_CALL(mockStringManipulation, stripWhite(curTest))
.RETURN(curTest);
REQUIRE_CALL(mockStringManipulation, FindFirstOf(curTest, cstring("//")))
.RETURN(NPOS);
REQUIRE_CALL(mockStringManipulation, FindLastOf(curTest, '\n'))
.RETURN(5);
REQUIRE_CALL(mockStringManipulation, Substring(curTest, 0, 6))
.RETURN(test);

FastString result = StripComments(curTest);
CHECK_THAT(result.cstring, Equals("test"));
}
}
}
