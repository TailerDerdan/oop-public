#include "modules.h"

int main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	
	numbers = ReadVector(numbers);
	numbers = MultiplyByMinElement(numbers);
	WriteVector(numbers);

	return EXIT_SUCCESS;
}