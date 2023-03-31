#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <iterator>

std::set<int> GeneratePrimeNumbers(int upperBound)
{
	std::set<int> result;
	std::vector<bool> primeNumbers = std::vector<bool>(upperBound, false);
	for (size_t i = 2; i*i <= upperBound; ++i)
	{
		size_t j = i + i;
		while (j < upperBound)
		{
			primeNumbers.at(j) = true;
			j += i;
		}
		if (!primeNumbers.at(i))
		{
			result.insert(i);
		}
	}
	for (size_t i = std::sqrt(upperBound); i < upperBound; ++i)
	{
		if (!primeNumbers.at(i))
		{
			result.insert(i);
		}
	}
	return result;
}

int main()
{
	size_t upperBound = 100000000;
	std::set<int> primeNumber = GeneratePrimeNumbers(upperBound);

	std::cout << primeNumber.size() << std::endl;

	return 0;
}
