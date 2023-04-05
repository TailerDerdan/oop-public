#include "modules.h"

std::set<int> TheSieveOfErotosfen(int upperBound)
{
	std::set<int> result;
	if (upperBound < 2)
	{
		return result;
	}
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