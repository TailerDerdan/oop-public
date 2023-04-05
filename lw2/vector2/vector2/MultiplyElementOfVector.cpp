#include "modules.h"

std::vector<double> ReadVector(std::vector<double>& numbers)
{
	std::copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), std::back_inserter(numbers));
	return numbers;
}

std::vector<double> MultiplyByMinElement(std::vector<double>& numbers)
{
	std::vector<double> result = numbers;
	if (!numbers.empty())
	{
		const double min = *std::min_element(result.begin(), result.end());
		std::transform(result.begin(), result.end(), result.begin(), [&min](double& num) { return num * min; });
	}

	return result;
}

void WriteVector(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
	if (!numbers.empty())
	{
		copy(numbers.begin(), numbers.end() - 1, std::ostream_iterator<double>(std::cout, ", "));
		std::cout << *(numbers.end() - 1);
	}
	else
	{
		copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, ", "));
	}
	
}