#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>

using Mat3x3 = std::array<std::array<double, 3>, 3>;

struct Args {
	std::string matrixInputFile1;
	std::string matrixInputFile2;
};

//переименовать функцию
std::optional<Mat3x3> ReadMatrix(const std::string& fileName)
{
	std::ifstream matrixInputFile;
	matrixInputFile.open(fileName);
	if (!matrixInputFile.is_open())
	{
		std::cout << "Failed to open '" << fileName << "' for reading" << std::endl;
		return std::nullopt;
	}

	Mat3x3 matrix;
	int col = 0;//перепутанны названия
	int row = 0;
	double num = 0;

	while (matrixInputFile >> num && row < 3)
	{
		if (col == 3)
		{
			col = 0;
			++row;
		}
		matrix[row][col] = num;
		++col;
	}
	if (row < 2)
	{
		std::cout << "Please enter matrix 3*3" << std::endl;
		return std::nullopt;
	}
	return matrix;
}

Mat3x3 Multiply(const Mat3x3& lhs, const Mat3x3& rhs)
{
	Mat3x3 result{0};
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				result[j][i] += lhs[j][k] * rhs[k][i];
			}
		}
	}
	return result;
}
//упрастить чтение матрицы

void MatrixOutput(const Mat3x3& m1)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << m1[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

//результирующую матрицу нужно проинициализировать в функции

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count" << std::endl;
		std::cout << "Usage: replace.exe <matrix1> <matrix2>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.matrixInputFile1 = argv[1];
	args.matrixInputFile2 = argv[2];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}
	//сделать 
	//считать матрицу 1, считать матрицу 2, 
	//перемножить матрицу
	//вывести матрицу

	auto m1 = ReadMatrix(args->matrixInputFile1);
	if (!m1)
	{
		return EXIT_FAILURE;
	}
	MatrixOutput(*m1);

	auto m2 = ReadMatrix(args->matrixInputFile2);
	if (!m2)
	{
		return EXIT_FAILURE;
	}

	auto m3 = Multiply(*m1, *m2);

	MatrixOutput(m3);

	return EXIT_SUCCESS;
}