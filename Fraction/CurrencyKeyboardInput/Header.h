#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right) { return left + rand() % (right + 1 - left); }
};

class IntegerToThousandSeparatedUIConverter {
private:
	std::string _thousandSeparator = ".";
public:
	bool isValidFormat(std::string);
	std::string convert(const unsigned long long&);
	std::tuple<bool, unsigned long long, std::string, int > convertBack(std::string);
	bool isDigit(std::string value);
};

class CurrencyDataReader {
public:
	std::vector<unsigned long long> GetAll();
};

#endif // !HEADER_H
