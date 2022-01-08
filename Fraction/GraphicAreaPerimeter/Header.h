#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#define PI 3.14

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right) { return left + rand() % (right + 1 - left); }
};

class Shape {
protected:

public:
	Shape() {}
	virtual std::string information() { return ""; }
	virtual float calculateArea() { return 0; }
	virtual float calculatePerimeter() { return 0; }
	virtual std::string display() { return ""; }
	virtual std::string displayAreaPerimeter() { return ""; }
};

class Rectangle: public Shape {
private:
	float _width;
	float _height;
public:
	Rectangle(float w, float h);
	float calculateArea();
	float calculatePerimeter();
	std::string display();
	std::string displayAreaPerimeter();
	std::string information();
};

class Circle: public Shape {
private:
	float _radius;
public:
	Circle(float r);
	float calculateArea();
	float calculatePerimeter();
	std::string display();
	std::string displayAreaPerimeter();
	std::string information();
};

class Triangle: public Shape {
private:
	float _a;
	float _b;
	float _c;
public:
	Triangle(float a, float b, float c);
	Triangle(const Triangle& t) {
		_a = t._a;
		_b = t._b;
		_c = t._c;
	}
	float calculateArea();
	float calculatePerimeter();
	std::string display();
	std::string displayAreaPerimeter();
	std::string information();
};

class RandomShapeGenerator {
private:
	RandomIntegerGenerator _rng;
public:
	void randomShape(Shape*& sh);
	void writeToFile(std::fstream& f, Shape*& sh);
};

#endif // !HEADER_H

