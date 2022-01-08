#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#define PI 3.14

class Shape {
private:
public:
	Shape() {}
	virtual std::string information() = 0;
	virtual float calculateArea() = 0;
	virtual float calculatePerimeter() = 0;
	virtual std::string display() = 0;
	virtual std::string displayAreaPerimeter() = 0;
	~Shape() {}
};

class Rectangle : public Shape {
private:
	float _width;
	float _height;
public:
	Rectangle(float w, float h);
	float calculateArea();
	float calculatePerimeter();
	std::string display();
	std::string displayAreaPerimeter();
	std::string information() { return "Rectangle: "; }
};

class Circle : public Shape {
private:
	float _radius;
public:
	Circle(float r);
	float calculateArea();
	float calculatePerimeter();
	std::string display();
	std::string displayAreaPerimeter();
	std::string information() { return "Circle: "; }
};

class Triangle : public Shape {
private:
	float _a;
	float _b;
	float _c;
public:
	Triangle(float a, float b, float c);
	float calculateArea();
	float calculatePerimeter();
	std::string display();
	std::string displayAreaPerimeter();
	std::string information() { return "Triangle: "; }
};

class ShapeDataReader {
private:
	std::string connectionString;
	std::vector<Shape*> list;
public:
	ShapeDataReader(std::string connectionstring) { connectionString = connectionstring; }
	std::vector<Shape*> getAll();
	Rectangle convertRectangle(std::string value);
	Triangle convertTriangle(std::string value);
	Circle convertCircle(std::string value);
	void printData(std::vector<Shape*> sh);
	~ShapeDataReader();
};

#endif // !HEADER_H

