#include <iostream>
#include <optional>
#include <string>
#include <cmath>

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

int LetterToNumber(const char& ch, bool& wasError)
{
	if ((ch >= '0') && (ch <= '9'))
	{
		wasError = false;
		return ch - '0';
	}
	else if ((ch >= 'A') && (ch <= 'Z'))
	{
		wasError = false;
		return ch - '0' - 7;
	}
	else
	{
		wasError = true;
		return EXIT_FAILURE;
	}
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	if ((str.empty()) || (radix < 2) || (radix > 36))
	{
		wasError = true;
		return EXIT_FAILURE;
	}

	int i = 0;
	long long result = 0;
	int numberInStr = 0;

	bool identifierNeg = false;

	if (str[i] == '-')
	{
		identifierNeg = true;
		i = 1;
	}

	while (i <= str.length() - 1)
	{
		numberInStr = LetterToNumber(str[i], wasError);
		if ((wasError) || (numberInStr > radix))
		{
			wasError = true;
			return EXIT_FAILURE;
		}
		if (result >= ((INT32_MAX - numberInStr) / radix))
		{
			result %= INT32_MAX;
			if (result < 0)
			{
				result *= -1;
			}
		}
		result = result * radix + numberInStr;
		++i;
	}
	if (identifierNeg)
	{
		result *= -1;
	}
	return result;
}

char NumberToChar(int remain, bool& wasError)
{
	if ((remain >= 0) && (remain <= 9))
	{
		return remain + '0';
	}
	else if ((remain >= 10) && (remain <= 36))
	{
		return remain + '0' + 7;
	}
	else
	{
		wasError = true;
		return '-';
	}
}

void Reverse(std::string& str)
{
	for (int i = 0; i < str.length() / 2; ++i)
	{
		std::swap(str[i], str[str.length() - i - 1]);
	}
}

std::string IntToString(int n, int radix, bool& wasError)
{
	std::string str;
	if ((radix < 2) || (radix > 36))
	{
		wasError = true;
		return str;
	}

	bool identifierNeg = false;
	if (n < 0)
	{
		identifierNeg = true;
		n *= -1;
	}

	int remain = 0;
	int quoit = 0;

	while (n >= radix)
	{
		remain = n % radix;
		n -= remain;
		n /= radix;
		str.push_back(NumberToChar(remain, wasError));
		if (wasError)
		{
			str.clear();
			return str;
		}
	}
	remain = n % radix;
	str.push_back(NumberToChar(remain, wasError));
	if (wasError)
	{
		str.clear();
		return str;
	}
	if (identifierNeg)
	{
		str.push_back('-');
	}
	Reverse(str);
	return str;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <SourceNotation> <DestinationNotation> <value>\n";
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];

	return args;
}

bool CheckedError(bool err)
{
	if (err)
	{
		std::cout << "Incorrect data entry.\n";
		std::cout << "Please enter numbers or letter(A..Z)\n";
		return true;
	}
	return false;
}

bool TranslationNumber(const std::string& sourceNotation, const std::string& destinationNotation, const std::string& value)
{
	bool err = false;

	int sourceNotationInt = StringToInt(sourceNotation, 10, err);
	if (CheckedError(err))
	{
		return false;
	}

	int destinationNotationInt = StringToInt(destinationNotation, 10, err);
	if (CheckedError(err))
	{
		return false;
	}

	int valueInt = StringToInt(value, sourceNotationInt, err);
	if (CheckedError(err))
	{
		return false;
	}

	std::string result = IntToString(valueInt, destinationNotationInt, err);
	if (CheckedError(err))
	{
		return false;
	}

	if (!err)
	{
		std::cout << result << '\n';
	}
	
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	if (!TranslationNumber(args->sourceNotation, args->sourceNotation, args->value))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}