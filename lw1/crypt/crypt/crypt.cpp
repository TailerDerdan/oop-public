#include <iostream>
#include <optional>
#include <fstream>
#include <string>

struct Args
{
	std::string idCrypt;
	std::string input;
	std::string output;
	std::string key;
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

uint32_t GetBit(int& x, int p)
{
	return (x >> p) & ~(~0 << 1);
}

uint32_t MoveBit(uint32_t& x, int n)
{
	return (x << n);
}

int MixBit(int x)
{
	uint32_t temp = GetBit(x, 7);
	uint32_t result = 0;
	result = result | MoveBit(temp, 5);
	temp = GetBit(x, 6);
	result = result | MoveBit(temp, 1);
	temp = GetBit(x, 5);
	result = result | MoveBit(temp, 0);
	temp = GetBit(x, 4);
	result = result | MoveBit(temp, 7);
	temp = GetBit(x, 3);
	result = result | MoveBit(temp, 6);
	temp = GetBit(x, 2);
	result = result | MoveBit(temp, 4);
	temp = GetBit(x, 1);
	result = result | MoveBit(temp, 3);
	temp = GetBit(x, 0);
	result = result | MoveBit(temp, 2);
	return result;
}

void Encryption(std::ifstream& input, std::ofstream& output, int key)
{
	char ch;
	int chNum = 0;
	while (input.get(ch))
	{
		chNum = int(ch);
		int result = chNum ^ key;
		result = MixBit(result);
		output.put(char(result));
	}
}

int ReverseMixBit(int x)
{
	uint32_t temp = GetBit(x, 7);
	uint32_t result = 0;
	result = result | MoveBit(temp, 4);
	temp = GetBit(x, 6);
	result = result | MoveBit(temp, 3);
	temp = GetBit(x, 5);
	result = result | MoveBit(temp, 7);
	temp = GetBit(x, 4);
	result = result | MoveBit(temp, 2);
	temp = GetBit(x, 3);
	result = result | MoveBit(temp, 1);
	temp = GetBit(x, 2);
	result = result | MoveBit(temp, 0);
	temp = GetBit(x, 1);
	result = result | MoveBit(temp, 6);
	temp = GetBit(x, 0);
	result = result | MoveBit(temp, 5);
	return result;
}

void DeEncryption(std::ifstream& input, std::ofstream& output, int key)
{
	char ch;
	int chNum = 0;
	while (input.get(ch))
	{
		chNum = int(ch);
		int result = ReverseMixBit(chNum);
		result = result ^ key;
		output.put(char(result));
	}
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <crypt> <key>\n";
		return std::nullopt;
	}
	Args args;
	args.input = argv[1];
	args.output = argv[2];
	args.idCrypt = argv[3];
	args.key = argv[4];
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

bool CryptOrDecryptFile(const std::string& input, const std::string& output, const std::string& idCrypt, const std::string& key)
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

	bool err = false;
	int keyInt = StringToInt(key, 10, err);
	if (CheckedError)
	{
		return false;
	}

	if (idCrypt == "crypt")
	{
		Encryption(inputFile, outputFile, keyInt);
	}
	else if (idCrypt == "decrypt")
	{
		DeEncryption(inputFile, outputFile, keyInt);
	}
	else
	{
		std::cout << "Enter crypt or decrypt please\n";
		return false;
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

	if (!CryptOrDecryptFile(args->input, args->output, args->idCrypt, args->key))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}