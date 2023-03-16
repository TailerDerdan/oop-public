#include <iostream>
#include <optional>
#include <string>
#include <fstream>

struct Args {
	std::string matrix1;
	std::string matrix2;
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

bool CheckedError(bool err)
{
	if (err)
	{
		std::cout << "Incorrect data entry.\n";
		std::cout << "Please enter numbers or ','\n";
		return true;
	}
	return false;
}

void ReadLine(std::string& str, int(&matrixInt)[3][3], int j, bool& wasErr)
{
	size_t pos = 0;
	size_t foundPos = 0;

	int i = 0;

	while (foundPos <= str.length() && i < 3)
	{
		foundPos = str.find(',', pos);
		std::string temp;
		temp.append(str, pos, foundPos - pos);
		pos = foundPos + 2;

		bool err = false;
		int numCellMatrix = StringToInt(temp, 10, err);
		if (CheckedError(err))
		{
			wasErr = true;
		}
		matrixInt[j][i] = numCellMatrix;
		++i;
	}
	if (i < 3)
	{
		std::cout << "Please enter matrix 3*3\n";
		wasErr = true;
	}
}

void ReadMatrix(std::ifstream& matrix, int(&matrixInt)[3][3], bool& wasErr)
{
	std::string line;

	int j = 0;

	while (std::getline(matrix, line))
	{
		ReadLine(line, matrixInt, j, wasErr);
		if (CheckedError(wasErr))
		{
			break;
		}
		++j;
	}
	if (j < 3)
	{
		std::cout << "Please enter matrix 3*3\n";
		wasErr = true;
	}
}

void MatrixOutput(int matrixInt[][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << matrixInt[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

void MultMatrix(int(&matrixInt1)[3][3], int(&matrixInt2)[3][3], int(&matrixMult)[3][3], bool& wasErr)
{
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				if (matrixMult[j][i] > (INT32_MAX - matrixInt1[j][k] * matrixInt2[k][i]))
				{
					std::cout << "Overflow\n";
					wasErr = true;
				}
				matrixMult[j][i] += matrixInt1[j][k] * matrixInt2[k][i];
			}
		}
	}
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <matrix1> <matrix2>\n";
		return std::nullopt;
	}
	Args args;
	args.matrix1 = argv[1];
	args.matrix2 = argv[2];
	return args;
}

bool MultMatrix(const std::string& matrix1, const std::string& matrix2)
{
	std::ifstream matrix1File;
	std::ifstream matrix2File;

	matrix1File.open(matrix1);
	matrix2File.open(matrix2);

	if (!matrix1File.is_open())
	{
		std::cout << "Failed to open '" << matrix1 << "' for reading\n";
		return false;
	}

	if (!matrix2File.is_open())
	{
		std::cout << "Failed to open '" << matrix2 << "' for reading\n";
		return false;
	}

	bool err = false;

	int matrix1Int[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	ReadMatrix(matrix1File, matrix1Int, err);
	if (err)
	{
		return false;
	}

	int matrix2Int[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	ReadMatrix(matrix2File, matrix2Int, err);
	if (err)
	{
		return false;
	}
	
	int matrixMult[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	MultMatrix(matrix1Int, matrix2Int, matrixMult, err);
	if (err)
	{
		return false;
	}
	MatrixOutput(matrixMult);
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	if (!MultMatrix(args->matrix1, args->matrix2))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}