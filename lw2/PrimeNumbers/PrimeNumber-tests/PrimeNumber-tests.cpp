#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../PrimeNumbers/modules.h" 

SCENARIO("Checking for finding prime numbers")
{
	std::set<int> primeNums = TheSieveOfEratosfen(100);
	std::set<int> result = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	REQUIRE(primeNums == result);
}

#ifdef NDEBUG // код будет скомпилирован только release-конфигурации
SCENARIO("Check count of elements in set of prime numbers")
{
	std::set<int> primeNums = TheSieveOfEratosfen(100000000);
	REQUIRE(primeNums.size() == 5761455);
}
#endif

//добавить тест для нижней границы
SCENARIO("Check lower bound")
{
	std::set<int> primeNums = TheSieveOfEratosfen(2);
	REQUIRE(primeNums.size() == 1);
}

SCENARIO("Uncorrect input dates")
{
	std::set<int> primeNums = TheSieveOfEratosfen(-1);
	REQUIRE(primeNums.size() == 0);
}