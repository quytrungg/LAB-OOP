#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() {
		srand(time(NULL));
	}
	int next() {
		return rand();
	}
	int next(int ceiling);
	int next(int left, int right);
};

class Integer {
public:
	int gcd(int a, int b);
};

class Fraction {
private:
	int _num;
	int _den;
public:
	void setNum(int num);
	int getNum();
	void setDen(int den);
	int getDen();
	void randomFraction(int num, int den);
	void saveFraction(std::fstream& f, std::string filename);
};

class RandomFractionGenerator {
private:
	RandomIntegerGenerator _rng;
public:
	Fraction next();
};

#endif // !HEADER_H
