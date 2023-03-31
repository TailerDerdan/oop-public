#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>

//Использовать enum
struct Args
{
	std::string inputFile;
	std::string outputFile;
};

enum Cell
{
	isWall,
	isFilled,
	startFill,
	emptyCell
};

using FieldArray = std::array<std::array<Cell, 100>, 100>;

struct Coord
{
	int x = 0, y = 0;
};

struct StructField
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::vector<Coord> coordsStart;
	FieldArray field;
	int xMax = 0;
	int yMax = 0;
};

//сделать чтобы функция возвращала bool
//поместить параметры функции в struct field
//переименовать в readfield
//передовать istream

bool ReadField(const std::string& inputPath, std::ifstream& inputFile)
{
	inputFile.open(inputPath);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open '" << inputPath << "' for reading\n";
		return false;
	}
	return true;
}

bool ReadField(StructField& field, const std::string& inputPath)
{
	if (!ReadField(inputPath, field.inputFile))
	{
		return false;
	}

	char ch;
	int x = 0, y = 0;
	const int MAX_WIDTH = 100;
	while (field.inputFile.get(ch))
	{
		Coord Temp;
		if (ch == '\n')
		{
			++y;
			field.xMax = std::max(field.xMax, x);
			x = 0;
		}
		else if (x < MAX_WIDTH)//задать именованную константу
		{
			switch (ch)
			{
			case '#':
				field.field[x][y] = isWall;
				++x;
				break;
			case 'O':
				field.field[x][y] = startFill;
				Temp.x = x;
				Temp.y = y;
				field.coordsStart.push_back(Temp);
				++x;
				break;
			case ' ':
				field.field[x][y] = emptyCell;
				++x;
				break;
			default:
				std::cout << "Uncorrect character, please use '#', 'O', ' ', 'char for move to the next line' \n";
				return false;
			}
		}
	}
	field.yMax = y;
	return true;
}

void FillCell(StructField& field, int x, int y, std::vector<Coord>& result)
{
	Coord temporaryCoord;
	if (field.field[x][y] != isFilled && field.field[x][y] == emptyCell)         // Вверх
	{
		temporaryCoord.x = x;
		temporaryCoord.y = y;
		result.push_back(temporaryCoord);
		field.field[x][y] = isFilled;
		field.yMax = std::max(temporaryCoord.y, field.yMax);
		field.xMax = std::max(temporaryCoord.x, field.xMax);
	}
}

std::vector<Coord> GetCoordFilledCell(StructField& field, std::vector<Coord>& coordStartCell)
{
	std::vector<Coord> result;
	const int MAX_WIDTH = 100;
	const int MIN_WIDTH = 0;
	while (!coordStartCell.empty())
	{
		//перемменые с маленькой буквы
		Coord currentCell;
		//объявить в место ее использование
		currentCell = coordStartCell.at(coordStartCell.size() - 1);
		coordStartCell.pop_back();
		//магические числа
		//сложный код
		//устранить дублироввание кода(перенести в фукнцию)
		if ((currentCell.x <= MAX_WIDTH - 1) && (currentCell.x >= MIN_WIDTH) && 
			(currentCell.y <= MAX_WIDTH - 2) && (currentCell.y >= MIN_WIDTH + 1))
		{
			FillCell(field, currentCell.x, currentCell.y - 1, result);             // Вверх
			FillCell(field, currentCell.x, currentCell.y + 1, result);             // Вниз
		}
		if ((currentCell.x <= MAX_WIDTH - 2) && (currentCell.x >= MIN_WIDTH + 1) && 
			(currentCell.y <= MAX_WIDTH - 1) && (currentCell.y >= MIN_WIDTH))
		{
			FillCell(field, currentCell.x - 1, currentCell.y, result);             // Влево
			FillCell(field, currentCell.x + 1, currentCell.y, result);             // Вправо
		}
	}
	return result;
}

void Fill(StructField& field)
{
	std::vector<Coord> nextGenerationCell;

	nextGenerationCell = GetCoordFilledCell(field, field.coordsStart);
	while (!nextGenerationCell.empty())
	{
		nextGenerationCell = GetCoordFilledCell(field, nextGenerationCell);
	}
}

//передавать ostream
//перенести параметры функции в структуру
//Field с маленькой буквы
bool Rendering(StructField& field, const std::string& output)
{
	field.outputFile.open(output);
	if (!field.outputFile.is_open())
	{
		std::cout << "Failed to open '" << output << "' for writing\n";
		return false;
	}
	for (int i = 0; i <= field.yMax; ++i)
	{
		for (int j = 0; j < field.xMax; ++j)
		{
			auto& cell = field.field[j][i];
			if (cell == isFilled)
			{
				field.outputFile.put('.');
			}
			if (cell == emptyCell)
			{
				field.outputFile.put(' ');
			}
			if (cell == isWall)
			{
				field.outputFile.put('#');
			}
			if (cell == startFill)
			{
				field.outputFile.put('O');
			}
		}
		field.outputFile.put('\n');
	}
	return true;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFile = argv[1];
	args.outputFile = argv[2];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	StructField field;
	if (!ReadField(field, args->inputFile))
	{
		return EXIT_FAILURE;
	}

	Fill(field);

	if (!Rendering(field, args->outputFile))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}