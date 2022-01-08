#include "Header.h"

Rectangle::Rectangle(float w, float h) {
	this->_width = w;
	this->_height = h;
}

float Rectangle::calculateArea() {
	return this->_height * this->_width;
}

float Rectangle::calculatePerimeter() {
	return (this->_height + this->_width) * 2;
}

Circle::Circle(float r) {
	this->_radius = r;
}

float Circle::calculateArea() {
	return pow(this->_radius, 2) * PI;
}

float Circle::calculatePerimeter() {
	return this->_radius * 2 * PI;
}

Triangle::Triangle(float a, float b, float c) {
	this->_a = a;
	this->_b = b;
	this->_c = c;
}

float Triangle::calculateArea() {
	float p = (this->_a + this->_b + this->_c) / 2;
	return sqrt(p * (p - this->_a) * (p - this->_b) * (p - this->_c));
}

float Triangle::calculatePerimeter() {
	return this->_a + this->_b + this->_c;
}

std::string Rectangle::display() {
	std::stringstream ss;
	ss << "Width=" << this->_width << ", Height=" << this->_height;
	return ss.str();
}

std::string Circle::display() {
	std::stringstream ss;
	ss << "Radius=" << this->_radius;
	return ss.str();
}

std::string Triangle::display() {
	std::stringstream ss;
	ss << "A=" << this->_a << ", B=" << this->_b << ", C=" << this->_c;
	return ss.str();
}

std::string Rectangle::displayAreaPerimeter() {
	std::stringstream ss;
	ss << "Area=" << this->calculateArea() << ", Perimeter=" << this->calculatePerimeter();
	return ss.str();
}

std::string Circle::displayAreaPerimeter() {
	std::stringstream ss;
	ss << "Area=" << this->calculateArea() << ", Perimeter=" << this->calculatePerimeter();
	return ss.str();
}

std::string Triangle::displayAreaPerimeter() {
	std::stringstream ss;
	ss << "Area=" << this->calculateArea() << ", Perimeter=" << this->calculatePerimeter();
	return ss.str();
}

void ShapeDataReader::printData(std::vector<Shape*> sh) {
	for (int i = 0; i < sh.size(); i++) {
		std::cout << sh[i]->information() << " " << sh[i]->display() << " => " << sh[i]->displayAreaPerimeter() << "\n";
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

std::vector<Shape*> ShapeDataReader::getAll() {
	std::fstream f(this->connectionString, std::fstream::in);
	std::vector<Shape*> sh;
	Shape* s;
	std::string temp;
	if (!f) {
		std::cout << "Cannot open file";
		return sh;
	}
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

ShapeDataReader::~ShapeDataReader() {
	for (int i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}
