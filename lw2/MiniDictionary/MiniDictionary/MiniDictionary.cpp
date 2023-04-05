#include "modules.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	bool err = false;
	if (!UserInteractionsWithDictionary())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}