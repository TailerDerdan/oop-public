#include <iostream>
#include <string>
#include <fstream>
#include <optional>

struct Args
{
	std::string input;
	std::string output;
	std::string search;
	std::string replace;
};

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	//Объявлять переменные только в месте их использования
	//строка заменитель может быть пустой
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	size_t foundPos = 0;

	//Подумать над именованием перемменой
	//Перенести в место использования
	while (foundPos <= subject.length() - searchString.length())
	{
		foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos <= subject.length())
		{
			result += replacementString;
		}
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return std::nullopt;
	}
	Args args;
	args.input = argv[1];
	args.output = argv[2];
	args.search = argv[3];
	args.replace = argv[4];
	return args;
}

bool CopyFileWithReplacement(std::string& input, std::string& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open(input);
	outputFile.open(output);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open '" << input << "' for reading\n";
		return false;
	}

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open '" << output << "' for writing\n";
		return false;
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	//Не надо открывать файлы в main
	// *args
	if (!CopyFileWithReplacement(args->input, args->output, args->search, args->replace))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}