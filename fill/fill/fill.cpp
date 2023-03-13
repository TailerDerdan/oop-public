#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>

struct Args
{
	std::string inputFile;
	std::string outputFile;
};


struct Cell
{
	bool isWall = false;
	bool isFilled = false;
	bool startFill = false;
};

struct Coord
{
	int x = 0, y = 0;
};

void ReadFile(std::ifstream& inputFile, Cell(&Field)[100][100], std::vector<Coord>& Coords, int& xMax, int& yMax, bool& wasErr)
{
	char ch;
	int x = 0, y = 0;
	while (inputFile.get(ch))
	{
		Coord Temp;
		if (ch == '\n')
		{
			++y;
			xMax = std::max(xMax, x);
			x = 0;
		}
		else if (x < 100)
		{
			switch (ch)
			{
			case '#':
				Field[x][y].isWall = true;
				Field[x][y].isFilled = true;
				++x;
				break;
			case 'O':
				Field[x][y].startFill = true;
				Field[x][y].isFilled = true;
				Temp.x = x;
				Temp.y = y;
				Coords.push_back(Temp);
				++x;
				break;
			case ' ':
				++x;
				break;
			default:
				std::cout << "Uncorrect character, please use '#', 'O', ' ', 'char for move to the next line' \n";
				wasErr = true;
			}
		}
	}
	yMax = y;
}

std::vector<Coord> GetCoordFilledCell(std::vector<Coord>& CoordsStartCell, Cell(&Field)[100][100], int& xMax, int& yMax)
{
	std::vector<Coord> result;
	while (!CoordsStartCell.empty())
	{
		Coord CurrentCell;
		Coord Temp;
		CurrentCell = CoordsStartCell.at(CoordsStartCell.size() - 1);
		CoordsStartCell.pop_back();
		if ((CurrentCell.x <= 99) && (CurrentCell.x >= 0) && (CurrentCell.y <= 98) && (CurrentCell.y >= 1))
		{
			if (!Field[CurrentCell.x][CurrentCell.y - 1].isFilled)         // Вверх
			{
				Temp.x = CurrentCell.x;
				Temp.y = CurrentCell.y - 1;
				result.push_back(Temp);
				Field[CurrentCell.x][CurrentCell.y - 1].isFilled = true;
			}
			if (!Field[CurrentCell.x][CurrentCell.y + 1].isFilled)         // Вниз
			{
				Temp.x = CurrentCell.x;
				Temp.y = CurrentCell.y + 1;
				result.push_back(Temp);
				Field[CurrentCell.x][CurrentCell.y + 1].isFilled = true;
				yMax = std::max(Temp.y, yMax);
			}
		}
		if ((CurrentCell.x <= 98) && (CurrentCell.x >= 1) && (CurrentCell.y <= 99) && (CurrentCell.y >= 0))
		{
			if (!Field[CurrentCell.x - 1][CurrentCell.y].isFilled)         // Влево
			{
				Temp.x = CurrentCell.x - 1;
				Temp.y = CurrentCell.y;
				result.push_back(Temp);
				Field[CurrentCell.x - 1][CurrentCell.y].isFilled = true;
			}
			if (!Field[CurrentCell.x + 1][CurrentCell.y].isFilled)         // Вправо 
			{
				Temp.x = CurrentCell.x + 1;
				Temp.y = CurrentCell.y;
				result.push_back(Temp);
				Field[CurrentCell.x + 1][CurrentCell.y].isFilled = true;
				xMax = std::max(Temp.x, xMax);
			}
		}
	}
	return result;
}

void Fill(Cell(&Field)[100][100], std::vector<Coord>& CoordsStartCell, int& xMax, int& yMax)
{
	std::vector<Coord> NextGenerationCell;

	NextGenerationCell = GetCoordFilledCell(CoordsStartCell, Field, xMax, yMax);
	while (!NextGenerationCell.empty())
	{
		NextGenerationCell = GetCoordFilledCell(NextGenerationCell, Field, xMax, yMax);
	}
}

void Rendering(Cell(&Field)[100][100], std::ofstream& outputFile, int xMax, int yMax)
{
	for (int i = 0; i <= yMax; ++i)
	{
		for (int j = 0; j < xMax; ++j)
		{
			if ((Field[j][i].isFilled) && (!Field[j][i].isWall) && (!Field[j][i].startFill))
			{
				outputFile.put('.');
			}
			if ((!Field[j][i].isFilled) && (!Field[j][i].isWall) && (!Field[j][i].startFill))
			{
				outputFile.put(' ');
			}
			if (Field[j][i].isWall)
			{
				outputFile.put('#');
			}
			if (Field[j][i].startFill)
			{
				outputFile.put('O');
			}
		}
		outputFile.put('\n');
	}
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

bool FillShapes(const std::string& input, const std::string& output)
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

	std::vector<Coord> CoordsStartCell;

	Cell Field[100][100];
	int xMax = 0, yMax = 0;
	bool wasErr = false;

	ReadFile(inputFile, Field, CoordsStartCell, xMax, yMax, wasErr);
	if (wasErr)
	{
		return false;
	}

	Fill(Field, CoordsStartCell, xMax, yMax);
	Rendering(Field, outputFile, xMax, yMax);

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	if (!FillShapes(args->inputFile, args->outputFile))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}