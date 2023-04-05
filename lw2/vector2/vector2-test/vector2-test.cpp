#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector2/modules.h" 

SCENARIO("Multiply elements of empty vector given empty vector")
{
	std::vector<double> vector;
	REQUIRE(MultiplyByMinElement(vector).empty());
}

SCENARIO("Multiplay some elements of vector on min element")
{
	std::vector<double> vector = { -6, 5, 3.345, 7, 6, 2 };
	std::vector<double> correctVector = { -42, -36, -30, -20.07, -12, 36 };
	vector = MultiplyByMinElement(vector);
	WriteVector(vector);
	REQUIRE(vector == correctVector);
}