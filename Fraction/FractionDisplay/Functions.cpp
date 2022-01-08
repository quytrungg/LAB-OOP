#include "Header.h"

//Randomize number between 0->ceiling
int RandomIntegerGenerator::next(int ceiling) {
	return rand() % ceiling;
}

//Randomize number between left->right
int RandomIntegerGenerator::next(int left, int right) {
	return left + rand() % (right + 1 - left);
}

//Find the greatest commmon divisor of 2 numbers
int Integer::gcd(int a, int b) {
	if (a > b) return Integer::gcd(b, a);
	do {
		unsigned long long r = b % a;
		b = a;
		a = r;
	} while (a != 0);
	return b;
}

//Set numerator for fraction
void Fraction::setNum(int num) {
	this->_num = num;
}

//Get numerator for fraction
int Fraction::getNum() {
	return this->_num;
}

//Set denominator for fraction
void Fraction::setDen(int den) {
	this->_den = den;
}

//Get denominator for fraction
int Fraction::getDen() {
	return this->_den;
}

//Initialize numerator and denominator for fraction
void Fraction::randomFraction(int num, int den) {
	this->_num = num;
	this->_den = den;
}

//Reduce the fraction to its lowest term
Fraction Fraction::lowestTerm() {
	Fraction reduce;
	Integer obj;
	int temp = obj.gcd(this->_num, this->_den);
	this->_num /= temp;
	this->_den /= temp;
	reduce.setNum(this->_num);
	reduce.setDen(this->_den);
	return reduce;
}

//Random a full fraction
Fraction RandomFractionGenerator::next() {
	Fraction fr;
	fr.randomFraction(_rng.next(1, 50), _rng.next(1, 50));
	return fr;
}

//Convert fraction to string
std::string Fraction::toString() {
	std::stringstream out;
	out << this->_num << "/" << this->_den;
	return out.str();
}

//Display the fraction of its lowest term
std::string Fraction::DisplayLowestTerm() {
	std::stringstream out;
	this->lowestTerm();
	if (this->_den == 1) {
		out << this->_num;
	}
	else if (this->_num < this->_den) {
		out << this->_num << "/" << this->_den;
	}
	else if (this->_num > this->_den) {
		int temp = this->_num / this->_den;
		out << temp << "(" << (this->_num - temp * this->_den) << "/" << this->_den <<  ")";
	}
	return out.str();
}

//Display the fraction in decimal 
std::string Fraction::DisplayDecimal() {
	std::stringstream out;
	double temp = (double)this->_num / this->_den;
	out << std::setprecision(2) << std::fixed << temp;
	return out.str();
}

//Display the fraction in percentage
std::string Fraction::DisplayPercentage() {
	std::stringstream out;
	double temp = (double)this->_num / this->_den * 100;
	if (temp == (int)temp) {
		out << (int)temp << "%";
	}
	else if (temp * 10 == (int) (temp * 10)) {
		out << std::setprecision(1) << std::fixed << temp << "%";
	}
	else {
		out << std::setprecision(2) << std::fixed << temp << "%";
	}
	return out.str();
}
