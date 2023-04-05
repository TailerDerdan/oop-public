#include "modules.h"

int main()
{
	size_t upperBound = 100000000;
	std::set<int> primeNumber = TheSieveOfErotosfen(upperBound);

	std::cout << primeNumber.size() << std::endl;

	return 0;
}
