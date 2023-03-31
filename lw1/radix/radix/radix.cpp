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
	const int DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER = 7;
	const char CONST_FOR_CONVERT_CHAR_TO_DIGIT = '0';
	if (isdigit(ch))
	{
		wasError = false;
		return ch - CONST_FOR_CONVERT_CHAR_TO_DIGIT;
	}
	else if (isalpha(ch))
	{
		wasError = false;
		return ch - CONST_FOR_CONVERT_CHAR_TO_DIGIT - DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER;//TODO: use const
	}
	else
	{
		wasError = true;
		return EXIT_SUCCESS;//TODO: use 0
	}
}

int StringToInt(const std::string& str, int radix, bool& wasError, bool& wasErrorForOverflow)
{
	if ((str.empty()) || (radix < 2) || (radix > 36))
	{
		wasError = true;
		return EXIT_SUCCESS;//TODO: use 0
	}

	int i = 0;
	 //TODO: переменные можно обьявлять ближе к месту использования
	//TDOO: переименовать число символа

	bool isNegative = false; //TODO: isNegative
	const char negativeChar = '-';

	if (str[i] == negativeChar)//TODO: symbol to const
	{
		isNegative = true;
		i = 1;
	}

	long long result = 0;
	int charNumber = 0;

	while (i <= str.length() - 1)
	{
		charNumber = LetterToNumber(str[i], wasError);
		if ((wasError) || (charNumber > radix))
		{
			wasError = true;
			return EXIT_SUCCESS;
		}
		if (result >= ((INT32_MAX - charNumber) / radix))
		{
			//TODO: нужно вернуть ошибку
			wasErrorForOverflow = true;
			return EXIT_SUCCESS;
		}
		result = result * radix + charNumber;
		++i;
	}
	if (isNegative)
	{
		result *= -1;
	}
	return result;
}

char NumberToChar(int remain, bool& wasError)
{
	const int DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER = 7;
	const char CONST_FOR_CONVERT_CHAR_TO_DIGIT = '0';
	const char negativeChar = '-';

	if ((remain >= 0) && (remain <= 9))
	{
		return remain + CONST_FOR_CONVERT_CHAR_TO_DIGIT;
	}
	else if ((remain >= 10) && (remain <= 36))
	{
		return remain + CONST_FOR_CONVERT_CHAR_TO_DIGIT + DIF_BETW_NUMBER_OF_DIGIT_AND_LETTER;
	}
	else
	{
		wasError = true;
		return negativeChar;
	}
}

void Reverse(std::string& str)
{
	for (int i = 0; i < str.length() / 2; ++i)
	{
		std::swap(str[i], str[str.length() - i - 1]);
	}
}

std::string IntToString(int number, int radix, bool& wasError)
{
	std::string str;
	if ((radix < 2) || (radix > 36))
	{
		wasError = true;
		return str;
	}

	bool isNegative = false;
	if (number < 0)
	{
		isNegative = true;
		number *= -1;
	}

	int remain = 0;
	int quoit = 0;

	while (number >= radix)
	{
		remain = number % radix;
		number -= remain;
		number /= radix;

		str.push_back(NumberToChar(remain, wasError));
		if (wasError)
		{
			str.clear();
			return str;
		}
	}
	remain = number % radix;
	str.push_back(NumberToChar(remain, wasError));
	if (wasError)
	{
		str.clear();
		return str;
	}
	if (isNegative)
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
		//TODO: use const EOLN 
		std::cout << "Invalid argument count" << std::endl;
		std::cout << "Usage: replace.exe <SourceNotation> <DestinationNotation> <value>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];

	return args;
}

//TODO: переименовать на использование глагола
bool CheckError(bool err, bool errOverflow)
{
	if (err)
	{
		std::cout << "Incorrect data entry." << std::endl;
		std::cout << "Please enter numbers or letter(A..Z)" << std::endl;
		return true;
	}
	if (errOverflow)
	{
		std::cout << "Overflow" << std::endl;
		return true;
	}
	return false;
}

//TODO: переименовать на использование глагола
bool TranslateNumberFromSourceToDestination(const std::string& sourceNotation, const std::string& destinationNotation, const std::string& value)
{
	bool err = false;
	bool errOverflow = false;

	int sourceNotationInt = StringToInt(sourceNotation, 10, err, errOverflow);
	if (CheckError(err, errOverflow))
	{
		return false;
	}

	int destinationNotationInt = StringToInt(destinationNotation, 10, err, errOverflow);
	if (CheckError(err, errOverflow))
	{
		return false;
	}

	int valueInt = StringToInt(value, sourceNotationInt, err, errOverflow);
	if (CheckError(err, errOverflow))
	{
		return false;
	}

	std::string result = IntToString(valueInt, destinationNotationInt, err);
	if (CheckError(err, errOverflow))
	{
		return false;
	}

	if (!err)
	{
		std::cout << result << std::endl;
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

	if (!TranslateNumberFromSourceToDestination(args->sourceNotation, args->destinationNotation, args->value))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}