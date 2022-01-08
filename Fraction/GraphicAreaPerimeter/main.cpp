#include "Header.h"

int main() {
	RandomShapeGenerator _rsg;
	RandomIntegerGenerator _rng;
	std::fstream f("objects.txt", std::fstream::out);
	Shape* sh;
	int n = _rng.next(6, 12);
	std::cout << "Number of shapes: " << n << "\n";
	std::cout << "--------------------\n";
	for (int i = 0; i < n; i++) {
		_rsg.randomShape(sh);
		std::cout << sh->information() << sh->display() << " => " << sh->displayAreaPerimeter() << "\n";
		_rsg.writeToFile(f, sh);
		delete sh;
	}
	std::cout << "--------------------\n";
	std::cout << "Shapes have been written into \"objects.txt\" file!\n";
	std::cout << "--------------------\n";
	std::cout << "Press enter to end the program...";
	std::cin.get();
	f.close();
	return 0;
}
