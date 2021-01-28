#include "levenshtein_distance.h"
#include "test/catch.hpp"

using namespace std;

// Levenshtein distance exercise test case data version 1.0.0

TEST_CASE("empty strings")
{
    REQUIRE(0 == levenshtein::distance("", ""));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST_CASE("identical strings")
{
	REQUIRE(0 == levenshtein::distance("abcdefghij", "abcdefghij"));
}

TEST_CASE("only insertions")
{
	REQUIRE(4 == levenshtein::distance("", "abcd"));
}

TEST_CASE("only deletions")
{
	REQUIRE(4 == levenshtein::distance("abcd", ""));
}

TEST_CASE("only substitution")
{
	REQUIRE(1 == levenshtein::distance("lifo", "fifo"));
}

TEST_CASE("substitution and insertion")
{
	REQUIRE(3 == levenshtein::distance("mine", "times"));
}

TEST_CASE("substitution and deletion")
{
	REQUIRE(3 == levenshtein::distance("times", "mine"));
}

TEST_CASE("with numbers")
{
	REQUIRE(3 == levenshtein::distance("abc123", "abd2234"));
}

TEST_CASE("with special characters")
{
	REQUIRE(2 == levenshtein::distance("hello world!", "helloworld"));
}

TEST_CASE("with capital letters")
{
	REQUIRE(13 == levenshtein::distance("Oxygen O2", "Carbondioxide CO2"));
}

#endif
