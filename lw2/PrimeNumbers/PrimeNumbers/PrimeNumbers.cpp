#include "modules.h"

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	const int UPPER_BOUND = stoi(args->upperBound);

	// верхняя граница задается через командную строку
	std::set<int> primeNumber = TheSieveOfEratosfen(UPPER_BOUND); //переименовать функцию

	std::cout << primeNumber.size() << std::endl;

	return 0;
}
