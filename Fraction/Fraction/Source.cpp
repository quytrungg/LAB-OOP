#include "Header.h"

int main() {
	RandomIntegerGenerator _rng;
	RandomFractionGenerator _rfg;
	int n = _rng.next(10, 20);
	std::cout << "n = " << n << "\n";
	Fraction* fr = new Fraction[n];
	for (int i = 0; i < n; i++) {
		fr[i] = _rfg.next();
	}
	for (int i = 0; i < n; i++) {
		std::cout << fr[i].toString() << " ";
		fr[i].lowestTerm();
	}
	Fraction sum;
	sum.setNum(fr[0].getNum());
	sum.setDen(fr[0].getDen());
	for (int i = 1; i < n; i++) {
		sum = sum.add(fr[i]);
	}
	sum.lowestTerm();
	std::cout << "\nSum: " << sum.toString() << "\n";
	std::cin.get();
	return 0;
}