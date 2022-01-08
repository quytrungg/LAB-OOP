#include "Header.h"

int main() {
	FractionDataReader _fdr("data.txt");
	std::vector<Fraction> fr = _fdr.GetAll();
	FractionToStringUIConverter fts;
	std::cout << "------------------------------\n";
	std::cout << "Functions from UI:\n";
	for (int i = 0; i < fr.size(); i++) {
		std::cout << fr[i].toString() << ", ";
	}

	std::fstream f(_fdr.getString(), std::fstream::out);
	_fdr.ExportData(f, fr);
	f.close();

	Fraction sum = fr[0];
	for (int i = 1; i < fr.size(); i++) {
		sum = sum + fr[i];
	}
	std::cout << "\n------------------------------";
	std::cout << "\nSum = " << fts.convert(sum) << "\n";
	std::cout << "------------------------------\n";
	std::cout << "Press enter to end the program...\n";
	std::cin.get();
	return 0;
}
