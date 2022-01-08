#include "Header.h"

int main() {
	RandomIntegerGenerator _rng;
	RandomFractionGenerator _rfg;
	int n = _rng.next(15, 25);
	std::cout << "Number of fractions: " << n << "\n";
	Fraction* fr = new Fraction[n];
	std::cout << "List of fractions (Raw random): \n";
	for (int i = 0; i < n; i++) {
		fr[i] = _rfg.next();
		std::cout << fr[i].toString() << ", ";
	}
	std::cout << "\nList of fractions (Lowest term): \n";
	for (int i = 0; i < n; i++) {
		std::cout << fr[i].DisplayLowestTerm() << ", ";
	}
	std::cout << "\nList of fractions (Decimal): \n";
	for (int i = 0; i < n; i++) {
		std::cout << fr[i].DisplayDecimal() << ", ";
	}
	std::cout << "\nList of fractions (Percentage): \n";
	for (int i = 0; i < n; i++) {
		std::cout << fr[i].DisplayPercentage() << ", ";
	}

	std::cin.get();
	return 0;
}