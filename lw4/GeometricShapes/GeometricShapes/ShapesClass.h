#pragma once
#include <string>
#include <vector>
#include <memory>

class CPoint
{
public:
	CPoint();
	CPoint(double xCoord, double yCoord);

	double GetXCoord() const;
	double GetYCoord() const;
	void operator=(const CPoint& coord);

	~CPoint();
private:
	double x;
	double y;
};

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimetr() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};

class CLineSegment : public IShape
{
public:

	double GetArea() const override;
	double GetPerimetr() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	bool CheckingCorrectnessData(const std::string& data);

	~CLineSegment();
private:
	double area;
	double perimetr;
	uint32_t outlineColor;

	CPoint startPoint;
	CPoint endPoint;
};

class CTriangle : public ISolidShape 
{
public:

	double GetArea() const override;
	double GetPerimetr() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor()  const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	bool CheckingCorrectnessData(const std::string& data);

	double GetLengthLine(const CPoint& vertex1, const CPoint& vertex2) const;

private:
	double area;
	double perimetr;
	uint32_t outlineColor;
	uint32_t outFillColor;

	CPoint verterx1;
	CPoint verterx2;
	CPoint verterx3;
};

class CRectangle : public ISolidShape
{
public:
	CRectangle();

	double GetArea() const override;
	double GetPerimetr() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor()  const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	bool CheckingCorrectnessData(const std::string& data);

	~CRectangle();
private:
	double area;
	double perimetr;
	uint32_t outlineColor;
	uint32_t outFillColor;

	double width;
	double height;
	CPoint leftTop;
	CPoint rightBottom;
};

class CCircle : public ISolidShape
{
public:
	CCircle();

	double GetArea() const override;
	double GetPerimetr() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor()  const override;

	CPoint GetCenter() const;
	double GetRadius() const;

	bool CheckingCorrectnessData(const std::string& data);
	~CCircle();

private:
	double area;
	double perimetr;
	uint32_t outlineColor;
	uint32_t outFillColor;

	CPoint center;
	double rad;
};

class Memory
{
public:
	void GetShapeWithBiggestSquare() const;
	void GetShapeWithSmallestPerimetr() const;

	void AddShape(const std::shared_ptr<IShape>& shape);

private:
	std::vector<std::shared_ptr<IShape>> arrayOfShapes;
};