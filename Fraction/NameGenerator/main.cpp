#include "Header.h"

int main() {
	RandomIntegerGenerator _rng;
	RandomVietnamFullnameGenerator _name;
	int n = _rng.next(10, 20);
	std::cout << "Number of names generated: " << n << "\n";
	for (int i = 0; i < n; i++) {
		std::cout << _name.next(_rng.next(30)) << "\n";
	}
	std::cin.get();
	return 0;
}