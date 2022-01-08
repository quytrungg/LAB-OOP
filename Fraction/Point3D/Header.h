#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right) { return left + rand() % (right + 1 - left); }
};

class Point2D {
protected:
	int _x;
	int _y;
public:
	Point2D(){}
	Point2D(int x, int y);
    friend std::istream& operator>>(std::istream& is, Point2D& p);
    friend std::ostream& operator<<(std::ostream& os, Point2D p);
	//std::string toString();
};

class Point3D: public Point2D {
private:
	int _z;
public:
	Point3D(){}
	Point3D(int x, int y, int z);
	friend std::istream& operator>>(std::istream& is, Point3D& p);
	friend std::ostream& operator<<(std::ostream& os, Point3D p);
	std::string toString();
};

class PointDataReader {
public:
	void writeToFile(std::fstream& f, Point2D* &p, int n);
	void writeToFile(std::fstream& f, Point3D* &p, int n);
};


#endif // !HEADER_H

