#include "modules.h"
#include <algorithm>
#include <vector>
#include <iterator>

std::set<int> TheSieveOfEratosfen(int upperBound)
{
	const int LOWER_BOUND = 2;
	std::set<int> result;
	if (upperBound < LOWER_BOUND)
	{
		return result;
	}
	// почитать про vector<bool>
	// Numbers => isCompound, sieve
	std::vector<bool> isCompound = std::vector<bool>(upperBound, false);
	
	for (int num = LOWER_BOUND; num <= std::ceil(std::sqrt(upperBound)) + 1; ++num)
	{
		size_t primeNum = num + num;
		while (primeNum < upperBound)
		{
			// at => []
			isCompound[primeNum] = true;
			primeNum += num;
		}
	}
	for (int num = LOWER_BOUND; num < upperBound; ++num) // warning
	{
		if (!isCompound[num])
		{
			result.insert(num);
		}
	}
	if (!isCompound[upperBound - 1])
	{
		result.insert(upperBound);
	}
	return result;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count" << std::endl << "Usage: primenumber.exe <upperBound>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.upperBound = argv[1];
	return args;
}