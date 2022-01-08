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

void RandomShapeGenerator::randomShape(Shape*& sh) {
	int n = this->_rng.next(0, 2);
	if (n == 0) {
		sh = new Rectangle(this->_rng.next(1, 10), this->_rng.next(1, 10));
	}
	else if (n == 1) {
		sh = new Circle(this->_rng.next(1, 10));
	}
	else {
		int a, b, c;
		do {
			a = this->_rng.next(1, 10);
			b = this->_rng.next(1, 10);
			c = this->_rng.next(1, 10);
		} while (a + b <= c || a + c <= b || b + c <= a);
		sh = new Triangle(a, b, c);
	}
}

void RandomShapeGenerator::writeToFile(std::fstream& f, Shape*& sh) {
	f << sh->information() << sh->display() << " => " << sh->displayAreaPerimeter() << "\n";
}

std::string Rectangle::information() {
	return "Rectangle: ";
}

std::string Circle::information() {
	return "Circle: ";
}

std::string Triangle::information() {
	return "Triangle: ";
}


