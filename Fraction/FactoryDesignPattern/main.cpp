#include "Header.h"

int main() {
	ShapeDataReader sdr("data.txt");
	std::vector<Shape*> sh = sdr.getAll();
	sdr.printData(sh);
	std::cout << "--------------------\n";
	std::cout << "Press enter to end the program...";
	std::cin.get();
	return 0;
}

