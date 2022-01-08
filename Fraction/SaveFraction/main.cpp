#include "Header.h"

int main() {
	RandomIntegerGenerator _rng;
	RandomFractionGenerator _rfg;
	std::fstream f("fractions.txt", std::fstream::out);
	int n = _rng.next(15, 25);
	std::cout << "Number of fractions: " << n << "\n";
	Fraction* fr = new Fraction[n];
	std::cout << "Fractions have been written in fractions.txt file\n";
	for (int i = 0; i < n; i++) {
		fr[i] = _rfg.next();
		f << fr[i].getNum() << "/" << fr[i].getDen() << "\n";
	}
	f.close();
	std::cin.get();
	return 0;
}
