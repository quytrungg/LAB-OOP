#include "Header.h"

int main() {
	RandomIntegerGenerator _rng;
	PointDataReader _pdr;
	int n = _rng.next(3, 7);
	std::cout << "Number of points: " << n << "\n";
	Point3D* p = new Point3D[n];
	std::cout << "Please input: \n";
	for (int i = 0; i < n; i++) {
		std::cin >> p[i];
	}
	std::cout << "--------------------\n";
	std::cout << "Points: \n";
	for (int i = 0; i < n; i++) {
		std::cout << p[i] << "\n";
	}
	std::fstream f("data.txt", std::fstream::out);
	_pdr.writeToFile(f, p, n);
	f.close();
	std::cout << "--------------------\n";
	std::cout << "Your data has been saved to \"data.txt\" file\n";

	std::cout << "\nPlease enter to end to program...";
	std::cin.get();
	return 0;
}

