#include "ShapesClass.h"
#include <regex>
#include <cmath>
#include <numbers>
#include <iostream>
#include <iterator>
#include <sstream>

CPoint::CPoint()
{
	x = 0;
	y = 0;
}

CPoint::CPoint(double xCoord, double yCoord)
{
	x = xCoord;
	y = yCoord;
}

double CPoint::GetXCoord() const
{
	return x;
}

double CPoint::GetYCoord() const
{
	return y;
}

void CPoint::operator=(const CPoint& coord)
{
	this->x = coord.GetXCoord();
	this->y = coord.GetYCoord();
}

CPoint::~CPoint()
{
	x = 0;
	y = 0;
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimetr() const
{
	double xStart = startPoint.GetXCoord();
	double yStart = startPoint.GetYCoord();
	double xEnd = endPoint.GetXCoord();
	double yEnd = endPoint.GetYCoord();

	return std::sqrt( (xStart - xEnd)*(xStart - xEnd) + (yStart - yEnd)*(yStart - yEnd));
}

std::string CLineSegment::ToString() const
{
	return "Start Coord(" + std::to_string(GetStartPoint().GetXCoord()) + ";" + std::to_string(GetStartPoint().GetYCoord())
		+ "), End Coord(" + std::to_string(GetEndPoint().GetXCoord()) + ";" + std::to_string(GetEndPoint().GetYCoord()) + ") ";
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return endPoint;
}

bool CLineSegment::CheckingCorrectnessData(const std::string& data)
{
	size_t foundPosSpaceNext = 0;
	size_t foundPosSpaceLast = 0;

	std::vector<double> dataValues;
	int countCoord = 0;
	std::regex valueColor(R"(^#([A-Fa-f0-9]{6}$)");

	while (foundPosSpaceNext <= data.size())
	{
		foundPosSpaceLast = foundPosSpaceNext;
		foundPosSpaceNext = data.find(" ", foundPosSpaceNext, 1);
		std::string value;
		value.append(data, foundPosSpaceLast, foundPosSpaceNext- foundPosSpaceLast);

		std::smatch valueColorMatch;
		if (std::regex_match(value, valueColorMatch, valueColor))
		{
			outlineColor = std::stoi(value);
			break;
		}
		double valueD = std::stod(value);
		if (valueD == NAN)
		{
			return false;
		}
		dataValues.push_back(valueD);
		countCoord++;
	}

	if (countCoord != 4)
	{
		return false;
	}

	CPoint startCoord(dataValues.at(1), dataValues.at(2));
	CPoint endCoord(dataValues.at(3), dataValues.at(4));

	startPoint = startCoord;
	endPoint = endCoord;

	return true;
}

CLineSegment::~CLineSegment()
{
	area = 0;
	perimetr = 0;
	outlineColor = 0;
	startPoint.~CPoint();
	endPoint.~CPoint();
}

double CTriangle::GetLengthLine(const CPoint& vertex1, const CPoint& vertex2) const
{
	double xVertex1 = vertex1.GetXCoord();
	double yVertex1 = vertex1.GetYCoord();

	double xVertex2 = vertex2.GetXCoord();
	double yVertex2 = vertex2.GetYCoord();

	return std::sqrt((xVertex1 - xVertex2)*(xVertex1 - xVertex2) + (yVertex1 - yVertex2)*(yVertex2 - yVertex2));
}

double CTriangle::GetArea() const
{
	double AB = GetLengthLine(verterx1, verterx2);
	double BC = GetLengthLine(verterx2, verterx3);
	double CA = GetLengthLine(verterx3, verterx1);

	double polPerimetr = GetPerimetr() / 2;

	return std::sqrt(polPerimetr*(polPerimetr - AB)*(polPerimetr - BC)*(polPerimetr - CA));
}

double CTriangle::GetPerimetr() const
{
	double AB = GetLengthLine(verterx1, verterx2);
	double BC = GetLengthLine(verterx2, verterx3);
	double CA = GetLengthLine(verterx3, verterx1);

	return AB + BC + CA;
}

std::string CTriangle::ToString() const
{
	return "Vertex1(" + std::to_string(GetVertex1().GetXCoord()) + ";" + std::to_string(GetVertex1().GetYCoord())
		+ "), Vertex2(" + std::to_string(GetVertex2().GetXCoord()) + ";" + std::to_string(GetVertex2().GetYCoord())
		+ "), Vertex3(" + std::to_string(GetVertex3().GetXCoord()) + ";" + std::to_string(GetVertex3().GetYCoord()) + ") ";
}

uint32_t CTriangle::GetOutlineColor() const
{
	return outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return outFillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return verterx1;
}

CPoint CTriangle::GetVertex2() const
{
	return verterx2;
}

CPoint CTriangle::GetVertex3() const
{
	return verterx3;
}

bool CTriangle::CheckingCorrectnessData(const std::string& data)
{
	size_t foundPosSpaceNext = 0;
	size_t foundPosSpaceLast = 0;

	std::vector<double> dataValues;
	int countCoord = 0;

	std::regex valueColor(R"(^#([A-Fa-f0-9]{6}$)");
	bool isOutlineColor = false;
	bool isOutfillColor = false;

	while (foundPosSpaceNext <= data.size())
	{
		foundPosSpaceLast = foundPosSpaceNext;
		foundPosSpaceNext = data.find(" ", foundPosSpaceNext, 1);
		std::string value;
		value.append(data, foundPosSpaceLast, foundPosSpaceNext - foundPosSpaceLast);

		std::smatch valueColorMatch;
		if (std::regex_match(value, valueColorMatch, valueColor) && !isOutlineColor)
		{
			std::stringstream hexstream;
			hexstream << std::hex << value; 
			hexstream >> outlineColor;
			isOutlineColor = true;
		}
		if (std::regex_match(value, valueColorMatch, valueColor) && !isOutfillColor)
		{
			std::stringstream hexstream;
			hexstream << std::hex << value;
			hexstream >> outFillColor;
			isOutfillColor = true;
			break;
		}

		double valueD = std::stod(value);
		if (valueD == NAN)
		{
			return false;
		}
		dataValues.push_back(valueD);
		countCoord++;
	}

	if (countCoord != 6)
	{
		return false;
	}

	CPoint coordVertex1(dataValues.at(1), dataValues.at(2));
	CPoint coordVertex2(dataValues.at(3), dataValues.at(4));
	CPoint coordVertex3(dataValues.at(5), dataValues.at(6));

	verterx1 = coordVertex1;
	verterx2 = coordVertex2;
	verterx3 = coordVertex3;

	return true;
}

CRectangle::CRectangle()
{
	area = 0;
	perimetr = 0;
	outFillColor = 0;
	outlineColor = 0;
	width = 0;
	height = 0;
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimetr() const
{
	return 2*(GetWidth() + GetHeight());
}

std::string CRectangle::ToString() const
{
	return "LeftTop(" + std::to_string(GetLeftTop().GetXCoord()) + ";" + std::to_string(GetLeftTop().GetYCoord())
		+ "), RightBottom(" + std::to_string(GetRightBottom().GetXCoord()) + ";" + std::to_string(GetRightBottom().GetYCoord())
		+ "), Width(" + std::to_string(GetWidth()) + "), Height(" + std::to_string(GetHeight()) + ") ";
}

uint32_t CRectangle::GetOutlineColor() const
{
	return outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return outFillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return rightBottom;
}

double CRectangle::GetWidth() const
{
	return width;
}

double CRectangle::GetHeight() const
{
	return height;
}

bool CRectangle::CheckingCorrectnessData(const std::string& data)
{
	size_t foundPosSpaceNext = 0;
	size_t foundPosSpaceLast = 0;

	std::vector<double> dataValues;
	int countCoord = 0;

	std::regex valueColor(R"(^#([A-Fa-f0-9]{6}$)");
	bool isOutlineColor = false;
	bool isOutfillColor = false;

	while (foundPosSpaceNext <= data.size())
	{
		foundPosSpaceLast = foundPosSpaceNext;
		foundPosSpaceNext = data.find(" ", foundPosSpaceNext, 1);
		std::string value;
		value.append(data, foundPosSpaceLast, foundPosSpaceNext - foundPosSpaceLast);

		std::smatch valueColorMatch;
		if (std::regex_match(value, valueColorMatch, valueColor) && !isOutlineColor)
		{
			std::stringstream hexstream;
			hexstream << std::hex << value;
			hexstream >> outFillColor;
			isOutlineColor = true;
		}
		if (std::regex_match(value, valueColorMatch, valueColor) && !isOutfillColor)
		{
			std::stringstream hexstream;
			hexstream << std::hex << value;
			hexstream >> outFillColor;
			isOutfillColor = true;
			break;
		}

		double valueD = std::stod(value);
		if (valueD == NAN)
		{
			return false;
		}
		dataValues.push_back(valueD);
		countCoord++;
	}

	if (countCoord != 6)
	{
		return false;
	}
	
	CPoint leftTopCoord(dataValues.at(1), dataValues.at(2));
	CPoint rightBottomCoord(dataValues.at(3), dataValues.at(4));

	leftTop = leftTopCoord;
	rightBottom = rightBottomCoord;

	width = dataValues.at(5);
	height = dataValues.at(6);

	return true;
}

CRectangle::~CRectangle()
{
	area = 0;
	perimetr = 0;
	outFillColor = 0;
	outlineColor = 0;
	width = 0;
	height = 0;
	leftTop.~CPoint();
	rightBottom.~CPoint();
}

CCircle::CCircle()
{
	area = 0;
	perimetr = 0;
	outlineColor = 0;
	outFillColor = 0;
	rad = 0;
}

double CCircle::GetArea() const
{
	return std::numbers::pi * GetRadius() * GetRadius();
}

double CCircle::GetPerimetr() const
{
	return std::numbers::pi * 2 * GetRadius();
}

std::string CCircle::ToString() const
{
	return "Center(" + std::to_string(GetCenter().GetXCoord()) + ";" + std::to_string(GetCenter().GetYCoord())
		+ "), Radius(" + std::to_string(GetRadius()) + ") ";
}

uint32_t CCircle::GetOutlineColor() const
{
	return outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return outFillColor;
}

CPoint CCircle::GetCenter() const
{
	return center;
}

double CCircle::GetRadius() const
{
	return rad;
}

bool CCircle::CheckingCorrectnessData(const std::string& data)
{
	size_t foundPosSpaceNext = 0;
	size_t foundPosSpaceLast = 0;

	std::vector<double> dataValues;
	int countCoord = 0;

	std::regex valueColor(R"(^#([A-Fa-f0-9]{6}$)");
	bool isOutlineColor = false;
	bool isOutfillColor = false;

	while (foundPosSpaceNext <= data.size())
	{
		foundPosSpaceLast = foundPosSpaceNext;
		foundPosSpaceNext = data.find(" ", foundPosSpaceNext, 1);
		std::string value;
		value.append(data, foundPosSpaceLast, foundPosSpaceNext - foundPosSpaceLast);

		std::smatch valueColorMatch;
		if (std::regex_match(value, valueColorMatch, valueColor) && !isOutlineColor)
		{
			std::stringstream hexstream;
			hexstream << std::hex << value;
			hexstream >> outFillColor;
			isOutlineColor = true;
		}
		if (std::regex_match(value, valueColorMatch, valueColor) && !isOutfillColor)
		{
			std::stringstream hexstream;
			hexstream << std::hex << value;
			hexstream >> outFillColor;
			isOutfillColor = true;
			break;
		}

		double valueD = std::stod(value);
		if (valueD == NAN)
		{
			return false;
		}
		dataValues.push_back(valueD);
		countCoord++;
	}

	if (countCoord != 3)
	{
		return false;
	}

	CPoint centerCoord(dataValues.at(1), dataValues.at(2));

	center = centerCoord;

	rad = dataValues.at(3);

	return true;
}

CCircle::~CCircle()
{
	area = 0;
	perimetr = 0;
	outlineColor = 0;
	outFillColor = 0;

	center.~CPoint();
	rad = 0;
}

void Memory::AddShape(const std::shared_ptr<IShape>& shape)
{
	arrayOfShapes.emplace_back(shape);
}