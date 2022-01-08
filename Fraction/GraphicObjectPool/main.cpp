#include "Header.h"

int main() {
	ShapeDataReader sdr("data.txt");
	ShapeDisplay sd;
	std::vector<Shape*> sh = sdr.getAll();
	sd.displayAllShape(sh);
	std::cout << "\nPress enter to end the program...";
	std::cin.get();
	return 0;
}
