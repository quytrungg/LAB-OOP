#include "Header.h"

Rectangle::Rectangle() {
	this->width = 0;
	this->height = 0;
}

Rectangle::Rectangle(float w, float h) {
	this->width = w;
	this->height = h;
}

void Rectangle::setShape(float a, float b, float c) {}

float Rectangle::calculateArea() {
	return this->height * this->width;
}

float Rectangle::calculatePerimeter() {
	return (this->height + this->width) * 2;
}

std::string Rectangle::display() {
	std::stringstream ss;
	ss << this->shapeType() << ": Width=" << this->width << ", Height=" << this->height 
		<< " => Area=" << this->calculateArea() << " Perimeter=" << this->calculatePerimeter();
	return ss.str();
}

Circle::Circle() {
	this->radius = 0;
}

Circle::Circle(float r) {
	this->radius = r;
}

void Circle::setShape(float a, float b, float c) {}

float Circle::calculateArea() {
	return pow(this->radius, 2) * PI;
}

float Circle::calculatePerimeter() {
	return this->radius * 2 * PI;
}

std::string Circle::display() {
	std::stringstream ss;
	ss << this->shapeType() << ": Radius=" << this->radius
		<< " => Area=" << this->calculateArea() << " Perimeter=" << this->calculatePerimeter();
	return ss.str();
}

Triangle::Triangle() {
	this->A = 0;
	this->B = 0;
	this->C = 0;
}

Triangle::Triangle(float a, float b, float c) {
	this->A = a;
	this->B = b;
	this->C = c;
}

void Triangle::setShape(float a, float b, float c) {}

float Triangle::calculateArea() {
	float p = (this->A + this->B + this->C) / 2;
	return sqrt(p * (p - this->A) * (p - this->B) * (p - this->C));
}

float Triangle::calculatePerimeter() {
	return this->A + this->B + this->C;
}

std::string Triangle::display() {
	std::stringstream ss;
	ss << this->shapeType() << ": A=" << this->A << ", B=" << this->B << ", C=" << this->C
		<< " => Area=" << this->calculateArea() << " Perimeter=" << this->calculatePerimeter();
	return ss.str();
}

std::string ShapeDisplay::outputShape(std::shared_ptr<Shape> shape) {
	return shape->display();
}

std::vector <Shape*> ShapeDataReader::getAll() {
	std::fstream f(this->connectionString, std::fstream::in);
	std::vector<Shape*> sh;
	Shape* s;
	std::string temp;
	if (!f) {
		std::cout << "Cannot open file";
		return sh;
	}
	std::shared_ptr<Shape> sha;
	while (!f.eof()) {
		std::getline(f, temp, '\n');
		if (temp == "") return sh;
		if (temp.find("Rectangle") != -1) {
			s = new Rectangle(this->convertRectangle(temp));
		}
		else if (temp.find("Triangle") != -1) {
			s = new Triangle(this->convertTriangle(temp));
		}
		else if (temp.find("Circle") != -1) {
			s = new Circle(this->convertCircle(temp));
		}
		else continue;
		sh.push_back(s);
	}
	return sh;
}

void ShapeDisplay::displayAllShape(std::vector<Shape*> sh) {
	for (int i = 0; i < sh.size(); i++) {
		std::cout << sh[i]->display() << "\n";
	}
}

Rectangle ShapeDataReader::convertRectangle(std::string value) {
	std::stringstream ss(value);
	std::string width, length;
	std::getline(ss, width, '=');
	std::getline(ss, width, ',');
	std::getline(ss, length, '=');
	std::getline(ss, length, '\n');
	return Rectangle(std::stof(width), std::stof(length));
}

Triangle ShapeDataReader::convertTriangle(std::string value) {
	std::stringstream ss(value);
	std::string a, b, c;
	std::getline(ss, a, '=');
	std::getline(ss, a, ',');
	std::getline(ss, b, '=');
	std::getline(ss, b, ',');
	std::getline(ss, c, '=');
	std::getline(ss, c, '\n');
	return Triangle(std::stof(a), std::stof(b), std::stof(c));
}

Circle ShapeDataReader::convertCircle(std::string value) {
	std::stringstream ss(value);
	std::string radius;
	std::getline(ss, radius, '=');
	std::getline(ss, radius, '\n');
	return Circle(std::stof(radius));
}
