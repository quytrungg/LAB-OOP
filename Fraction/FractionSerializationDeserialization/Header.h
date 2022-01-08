#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Fraction {
public:
	std::string separator = "/";
private:
	long long _num;
	long long _den;
public:
	long long Numerator() const { return _num; }
	long long Denominator() const { return _den; }
	void setNum(long long num) { _num = num; }
	void setDen(long long den) { _den = den; }
	void setFraction(long long num, long long den) { _num = num; _den = den; }
	Fraction reduceFraction();
	std::string toString();
};

class FractionToStringDataConverter {
public:
	std::string convert(Fraction& f);
	Fraction convertBack(std::string value);
	bool tryConvertBack(std::string value, Fraction& f);
	bool isValidFormat(std::string value);
};

class FractionDataReader {
private:
	std::string _connectionString;
public:
	FractionDataReader(std::string connectionString);
	std::string getString() { return _connectionString; }
public:
	std::vector<Fraction> GetAll();
	void OverwriteData(std::fstream& f, std::vector<Fraction> fr);
};

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right){ return left + rand() % (right + 1 - left); }
};

class Integer {
public:
	static long long gcd(long long a, long long b);
};

class RandomFractionGenerator {
private:
	RandomIntegerGenerator _rng;
public:
	Fraction next();
};

#endif // !HEADER_H
