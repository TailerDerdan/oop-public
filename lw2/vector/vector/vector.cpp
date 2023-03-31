#include "modules.h"

int main()
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	std::copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), std::back_inserter(numbers));
	std::sort(numbers.begin(), numbers.end());

	const double min = *numbers.begin();

	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [&min](double& num) { return num * min; });

	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, ", "));

	return EXIT_SUCCESS;
}