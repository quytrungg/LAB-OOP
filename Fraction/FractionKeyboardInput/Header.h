#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

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
	Fraction& operator=(const Fraction& p);
	void setFraction(int tu, int mau) { _num = tu; _den = mau; }
	Fraction reduceFraction();
	Fraction operator+(Fraction p);
	std::string toString();
};

class FractionToStringUIConverter {
public:
	std::string convert(Fraction& f);
	Fraction convertBacktemp(std::string value);
	bool isValidFormat(std::string value);
	std::tuple<bool, Fraction, int, std::string> convertBack(std::string);
	bool isDigit(std::string value);
};

class FractionDataReader {
private:
	std::string _connectionString;
public:
	FractionDataReader(std::string connectionString);
	std::string getString() { return _connectionString; }
public:
	std::vector<Fraction> GetAll();
	void ExportData(std::fstream& f, std::vector<Fraction> fr);
};

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right) { return left + rand() % (right + 1 - left); }
};

class Integer {
public:
	static long long gcd(long long a, long long b);
};

#endif // !HEADER_H

