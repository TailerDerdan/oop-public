#include "modules.h"

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	//TODO: не используется
	if (!UserInteractionsWithDictionary(args->input))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}