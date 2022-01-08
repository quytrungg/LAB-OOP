#include "Header.h"

int main() {
	ShopDataReader sdr;
	Category ca;
	Product pr;
	std::vector<Category> cate = sdr.GetCategory();
	std::vector<Product> prod = sdr.GetProduct();
	IntegerToThousandSeparatedUIConverter con;
	int option;
	std::string buffer, left, right;
	do {
		system("cls");
		std::cout << "What do you want to do?\n1. Display all categories\n2. Find products by name\n3. Find products by price range\n";
		std::cout << "\n0. Quit\n\nPlease enter your choice: ";
		std::cin >> option;
		switch (option)
		{
		case 1: {
			system("cls");
			for (int i = 0; i < cate.size(); i++) {
				std::cout << cate[i].getCategoryId() << ". " << cate[i].getCategoryName() << "\n";
			}
			std::cout << "\n Choose category: ";
			std::cin >> option;
			system("cls");
			ca.findCategory(option, prod, cate);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			std::cout << "Choose product: ";
			std::cin.ignore();
			std::getline(std::cin, buffer, '\n');
			system("cls");
			pr.findProduct(buffer, prod, cate);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			std::tuple<bool, int, std::string, int> res1, res2;
			do {
				std::cout << "Choose price range: ";
				std::cin >> left;
				std::cin >> right;
				res1 = con.convertBack(left);
				res2 = con.convertBack(right);
			} while (!std::get<0>(res1) || !std::get<0>(res2));
			system("cls");
			pr.findPrize(left, right, prod, cate);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 0:
			break;
		default: {
			std::cout << "Command not found!";
			std::cout << "\n";
			system("pause");
			break;
		}
		}
	} while (option != 0);
	system("cls");
	std::cout << "Press enter to exit the program...";
	std::cin.ignore();
	std::cin.get();
	return 0;
}
