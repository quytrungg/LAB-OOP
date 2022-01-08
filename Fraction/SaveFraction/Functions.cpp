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

//Random a full fraction
Fraction RandomFractionGenerator::next() {
	Fraction fr;
	fr.randomFraction(_rng.next(1, 50), _rng.next(1, 50));
	return fr;
}

void Fraction::saveFraction(std::fstream& f, std::string filename) {

}
