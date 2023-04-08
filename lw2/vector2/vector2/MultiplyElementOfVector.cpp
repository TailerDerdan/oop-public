#include "modules.h"

//возвращать void
void MultiplyByMinElement(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		const double min = *std::min_element(numbers.begin(), numbers.end());
		std::transform(numbers.begin(), numbers.end(), numbers.begin(), [min](double num) { return num * min; });
	}
}

void SortVector(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
}

//переименовать функцию и изменить передачу параметров по значению
void WriteSortedVector(std::vector<double> numbers)
{
	SortVector(numbers);
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