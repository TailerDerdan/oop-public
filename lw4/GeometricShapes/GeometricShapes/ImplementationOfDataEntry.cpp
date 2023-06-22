
#include "ModulesDataEntry.h"
#include <iostream>

void DataEntry()
{
	std::cout << "Format shape" << std::endl;
	std::cout << "Line: X1 Y1 X2 Y2 LineColor" << std::endl;
	std::cout << "Triangle: X1 Y1 X2 Y2 X3 Y3 LineColor ShapeColor" << std::endl;
	std::cout << "Rectangle: X1 Y1 X2 Y2 Width Height LineColor ShapeColor" << std::endl;
	std::cout << "Circle: X Y Radius LineColor ShapeColor" << std::endl;
	std::cout << "----------------------" << std::endl;

	Memory memory;
	std::string line;
	bool isShape = false;
	
	while (std::getline(std::cin, line))
	{
		size_t foundPosSpace = 0;
		foundPosSpace = line.find_first_of(" ");

		std::string typeShape;
		isShape = false;
		
		if (foundPosSpace <= line.size())
		{
			typeShape.append(line, 0, foundPosSpace);
			
			if (typeShape == "line")
			{
				std::shared_ptr<CLineSegment> lineShape = std::make_unique<CLineSegment>();
				line.erase(0, typeShape.size());
				if (lineShape->CheckingCorrectnessData(line))
				{
					std::shared_ptr<IShape> shape;
					shape = std::static_pointer_cast<IShape>(lineShape);
					memory.AddShape(shape);
					isShape = true;
				}
				
			}
			if (typeShape == "triangle")
			{
				std::shared_ptr<CTriangle> lineShape = std::make_unique<CTriangle>();
				line.erase(0, typeShape.size());
				if (lineShape->CheckingCorrectnessData(line))
				{
					std::shared_ptr<IShape> shape;
					shape = std::static_pointer_cast<IShape>(lineShape);
					memory.AddShape(shape);
					isShape = true;
				}
			}
			if (typeShape == "rectangle")
			{
				std::shared_ptr<CRectangle> lineShape = std::make_unique<CRectangle>();
				line.erase(1, typeShape.size());
				if (lineShape->CheckingCorrectnessData(line))
				{
					std::shared_ptr<IShape> shape;
					shape = std::static_pointer_cast<IShape>(lineShape);
					memory.AddShape(shape);
					isShape = true;
				}
			}
			if (typeShape == "circle")
			{
				std::shared_ptr<CCircle> lineShape = std::make_unique<CCircle>();
				line.erase(0, typeShape.size());
				if (lineShape->CheckingCorrectnessData(line))
				{
					std::shared_ptr<IShape> shape;
					shape = std::static_pointer_cast<IShape>(lineShape);
					memory.AddShape(shape);
					isShape = true;
				}
			}
			
		}
		if (!isShape)
		{
			std::cout << "You entered the wrong shape" << std::endl;
		}
	}

	//memory.GetShapeWithBiggestSquare();
	//memory.GetShapeWithSmallestPerimetr();

	
}