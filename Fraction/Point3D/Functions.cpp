#include "Header.h"

Point2D::Point2D(int x, int y) {
	this->_x = x;
	this->_y = y;
}

Point3D::Point3D(int x, int y, int z): Point2D(x, y) {
	this->_z = z;
}

std::istream& operator>>(std::istream& is, Point2D& p) {
	std::string point;
	std::getline(is, point, ',');
	p._x = std::stoi(point);
	std::getline(is, point, '\n');
	p._y = std::stoi(point);
	return is;
}

std::ostream& operator<<(std::ostream& os, Point2D p) {
	os << "(" << p._x << ", " << p._y << ")";
	return os;
}

std::istream& operator>>(std::istream& is, Point3D& p) {
	std::string point;
	std::getline(is, point, ',');
	p._x = std::stoi(point);
	std::getline(is, point, ',');
	p._y = std::stoi(point);
	std::getline(is, point, '\n');
	p._z = std::stoi(point);
	return is;
}

std::ostream& operator<<(std::ostream& os, Point3D p) {
	os << (Point2D)p;
	os << "\b, " << p._z << ")";
	return os;
}

std::string Point3D::toString() {
	std::stringstream ss;
	ss << "(" << this->_x << ", " << this->_y << ", " << this->_z << ")";
	return ss.str();
}

void PointDataReader::writeToFile(std::fstream& f, Point2D* &p, int n) {
	for (int i = 0; i < n; i++) {
		f << p[i] << "\n";
	}
}

void PointDataReader::writeToFile(std::fstream& f, Point3D* &p, int n) {
	for (int i = 0; i < n; i++) {
		f << p[i].toString() << "\n";
	}
}
