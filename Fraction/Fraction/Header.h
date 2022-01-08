#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ctime>
#include <sstream>

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() {
		srand(time(NULL));
	}
	int next() {
		return rand();
	}
	int next(int ceiling); // [0, ceiling)
	int next(int left, int right); // [left, right]
};

class Fraction {
private:
	unsigned long long _num;
	unsigned long long _den;
public:
	void setNum(int num);
	unsigned long long getNum();
	void setDen(int den);
	unsigned long long getDen();
	void randomFraction(unsigned long long num, unsigned long long den);
	Fraction lowestTerm();
	Fraction add(Fraction p);
	std::string toString();
};

class Integer {
public:
	static unsigned long long gcd(unsigned long long a, unsigned long long b);
};

class RandomFractionGenerator {
private:
	RandomIntegerGenerator _rng;
public:
	Fraction next();
};

#endif // !HEADER_H
