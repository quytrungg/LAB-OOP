#include "Header.h"

int main() {
	CurrencyDataReader cdr;
	IntegerToThousandSeparatedUIConverter itc;
	std::vector<unsigned long long> curr = cdr.GetAll();
	std::cout << "--------------------\n";
	std::cout << "Money from UI:\n";
	for (int i = 0; i < curr.size(); i++) {
		std::cout << itc.convert(curr[i]) << "\n";
	}
	std::cout << "--------------------\n";
	unsigned long long sum = curr[0];
	for (int i = 1; i < curr.size(); i++) {
		if (curr[i] > ULLONG_MAX || curr[i] > ULLONG_MAX - sum) {
			std::cout << "Money out of range!";
			exit(0);
		}
		sum += curr[i];
	}
	std::cout << "Sum = " << itc.convert(sum) << "\n";
	std::cout << "-------------------\n";
	std::cout << "Press enter to end the program...\n";
	std::cin.get();
	return 0;
}
