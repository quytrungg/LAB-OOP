#include "Header.h"

int RandomIntegerGenerator::next(int ceiling) {
	return rand() % ceiling;
}

int RandomIntegerGenerator::next(int left, int right) {
	return left + rand() % (right + 1 - left);
}

unsigned long long Integer::gcd(unsigned long long a, unsigned long long b) {
	if (a > b) return Integer::gcd(b, a);
	do {
		unsigned long long r = b % a;
		b = a;
		a = r;
	} while (a != 0);
	return b;
}

void Fraction::setNum(int num) {
	this->_num = num;
}

unsigned long long Fraction::getNum() {
	return this->_num;
}

void Fraction::setDen(int den) {
	this->_den = den;
}

unsigned long long Fraction::getDen() {
	return this->_den;
}

void Fraction::randomFraction(unsigned long long num, unsigned long long den) {
	this->_num = num;
	this->_den = den;
}

Fraction Fraction::lowestTerm() {
	Fraction reduce;
	unsigned long long temp = Integer::gcd(this->_num, this->_den);
	this->_num /= temp;
	this->_den /= temp;
	reduce.setNum(this->_num);
	reduce.setDen(this->_den);
	return reduce;
}

std::string Fraction::toString() {
	std::stringstream output;
	output << this->_num << "/" << this->_den;
	return output.str();
}

Fraction Fraction::add(Fraction p) {
	Fraction sum;
	sum._num = this->_num * p._den + p._num * this->_den;
	sum._den = this->_den * p._den;
	if (this->_num > ULLONG_MAX - p._num) {
		std::cout << "\nNumber exceeds unsigned long long range!";
		exit(0);
	}
	else if (this->_num > ULLONG_MAX / p._den || p._num > ULLONG_MAX / this->_den || this->_num * p._den > ULLONG_MAX - p._num * this->_den) {
		std::cout << "\nNumber exceeds unsigned long long range!";
		exit(0);
	}
	else if (this->_den > ULLONG_MAX / p._den) {
		std::cout << "\nNumber exceeds unsigned long long range!";
		exit(0);
	}
	else {
		sum.lowestTerm();
		return sum;
	}
}

Fraction RandomFractionGenerator::next() {
	Fraction fr;
	fr.randomFraction(_rng.next(1, 100), _rng.next(1, 100));
	return fr;
}
