#include "Header.h"

int main() {
	RandomFractionGenerator _rfg;
	FractionDataReader _fdr("data.txt");
	std::vector<Fraction> fr = _fdr.GetAll();
	FractionToStringDataConverter fts;
	std::cout << "\nThe fractions read from data.txt file:\n";
	for (int i = 0; i < fr.size(); i++)
		std::cout << fts.convert(fr[i]) << ", ";
	std::fstream f(_fdr.getString(), std::fstream::out);
	for (int i = 0; i < 2; i++) {
		Fraction temp = _rfg.next();
		fr.push_back(temp);
	}
	_fdr.OverwriteData(f, fr);
	std::cout << "\n\nThe fractions after adding 2 more random fractions in data.txt file:\n";
	for (int i = 0; i < fr.size(); i++)
		std::cout << fts.convert(fr[i]) << ", ";
	f.close();
	std::cout << "\n--------------------\nPress enter to exit the program";
	std::cin.get();
	return 0;
}
